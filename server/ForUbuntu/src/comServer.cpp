#include "include/comServer.h"
#include <algorithm>

  ComServer::ComServer(Chat &chat, bool & isExit):
      Observer(chat),
      m_isExit(isExit) {
  
  }


 void ComServer::update(const Message &messageFromChat){}

 void ComServer::run(){


    /*
    O_RDWR - чтение и запись
    O_NONBLOCK - не блокировать файл
    O_NOCTTY - не делать устройство управлящим терминалом
    O_NDELAY - не использовать DCD линию
    */
    m_fd = open(comServerIni.comPort, O_RDWR | O_NONBLOCK | O_NOCTTY | O_NDELAY);
    if (m_fd == -1) {
        perror("Unable to open port.(sudo adduser $USER dialout, sudo usermod -a -G $USER)?");
    }

    // clear all file status flags
    fcntl(m_fd, F_SETFL, 0);

    memset(&m_term, 0, sizeof(struct termios));

    if ((cfsetispeed(&m_term, comServerIni.speed) < 0) ||
        (cfsetospeed(&m_term, comServerIni.speed) < 0)) {
            perror("Unable to set baudrate");
    }

    /*
    CREAD - включить прием
    CLOCAL - игнорировать управление линиями с помошью
    */
    m_term.c_cflag |= (CREAD | CLOCAL);
    /* CSIZE - маска размера символа */
    m_term.c_cflag &= ~CSIZE;
    /* CS8 - 8 битные символы */
    m_term.c_cflag |= CS8;

    /* CSTOPB - при 1 - два стоп бита, при 0 - один */
    m_term.c_cflag &= ~CSTOPB;
 
    /*
    ICANON - канонический режим
    ECHO - эхо принятых символов
    ECHOE - удаление предыдущих символов по ERASE, слов по WERASE
    ISIG - реагировать на управляющие символы остановки, выхода, прерывания
    */
    m_term.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG);
    /* INPCK - вкл. проверку четности */
    m_term.c_iflag &= ~(INPCK);
    /* OPOST - режим вывода по умолчанию */
    m_term.c_oflag &= ~OPOST;

    /*
    TCSANOW - примернить изменения сейчасже
    TCSADRAIN - применить после передачи всех текущих данных
    TCSAFLUSH - приемнить после окончания передачи, все принятые но не считанные данные очистить
    */
    if (tcsetattr(m_fd, TCSANOW, &m_term) < 0)
    {
        perror("Unable to set port parameters");     
    }

    memset(m_tempBuf,0x00,sizeof(m_tempBuf));
    memset(m_buf,0x00,sizeof(m_buf));
     
    do{   
             
      m_res = read(m_fd,m_buf,512); 
      if (m_res > 0) {    
        for (m_countBuf = 0; m_countBuf  < m_res; m_countBuf++){
            
            if (m_countTempBuf > 511) { 
                printf("out of array tempBuf \n"); 
                std::exit(-1);  
                }
                //printf("check \n"); 
                m_tempBuf[m_countTempBuf] = m_buf[m_countBuf];
                printf("%02x ", m_tempBuf[m_countTempBuf]); 
                m_countTempBuf++;
            }
        printf("\n");
        printf("%02d %s %02d %s %d ", comServerIni.startByte[1], "  ", m_tempBuf[1], " num ", m_countTempBuf);
        printf("\n");
        if ( m_countTempBuf > 1 ){
          if (!(comServerIni.startByte[0] == m_tempBuf[0] &&\
              comServerIni.startByte[1] == m_tempBuf[1]&&\
              comServerIni.startByte[2] == m_tempBuf[2])){
              clearBuff();
          }
     
        } 
              
      }
          
      if ( m_countTempBuf >= comServerIni.numByte){ 
        m_command = ""; 
        printf("Read %d bytes:\n", m_countTempBuf);
        for (m_countBuf = 0; m_countBuf < comServerIni.numByte; m_countBuf ++){
            printf("%02x ", m_tempBuf[m_countBuf]); 
            m_command.append(decToHex(m_tempBuf[m_countBuf]));
        }   
        printf("\n");  
                   
        if (comServerIni.HexToCommannd.find(m_command)!= comServerIni.HexToCommannd.end()){
          m_messageToChat.m_message = comServerIni.HexToCommannd.at(m_command);
          m_messageToChat.m_to = "keyboardEmulator";
          sendMessageToChat(m_messageToChat);
        };

        clearBuff();
                
      }
      usleep(comServerIni.m_delayServerPoll); //задержка для считывания следующей комманды
    } while (!m_isExit);

 }

std::string ComServer::decToHex (unsigned char dec){
    if (dec == 0 ) return "00 ";
    std::ostringstream sout;
    int rem;
    const char *hex = "0123456789abcdef";
    
    while (dec > 0) {
      rem = dec % 16; 
      sout << hex[rem];
      dec = dec / 16;
    }
    
    std::string s(sout.str());
    std::reverse(s.begin(), s.end());
    s.append(" ");
    return s;
 }
 
 
 void ComServer::clearBuff (){
                  printf("%s","clear \n");
                  
                  do{ 
                    
                 //   for (int i = 0; i < 20; i++){
                      usleep(comServerIni.m_delayServerPoll);  
                 //     m_res = read(m_fd,m_buf,512);
                 //   }
                  
                  }while (read(m_fd,m_buf,512));
                  m_countTempBuf = 0;
                  memset(m_tempBuf,0x00,sizeof(m_tempBuf));
                  memset(m_buf,0x00,sizeof(m_buf));

 }