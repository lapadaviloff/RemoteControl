#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <termios.h> 
#include <cstdlib> 
#include <cstring>
#include <string>

/*программа просмотра com порта*/
int main()
{
    int fd;
    struct termios term;
    unsigned char buf[512];
    unsigned char tempBuf[512];
    int res;
    int countBuf = 0;
    int countTempBuf = 0;
    std::string port = "/dev/ttyUSB0"; //номер com - порта
    int numByte = 34; // кол - во байт, которые нужно прочитать
    /*
    O_RDWR - чтение и запись
    O_NONBLOCK - не блокировать файл
    O_NOCTTY - не делать устройство управлящим терминалом
    O_NDELAY - не использовать DCD линию
    */
    fd = open(port.c_str(), O_RDWR | O_NONBLOCK | O_NOCTTY | O_NDELAY);
    if (fd == -1) {
        perror("Unable to open port");
    }

    // clear all file status flags
    fcntl(fd, F_SETFL, 0);


#if 0
struct termios {
    tcflag_t c_iflag;      /* input modes */
    tcflag_t c_oflag;      /* output modes */
    tcflag_t c_cflag;      /* control modes */
    tcflag_t c_lflag;      /* local modes */
    cc_t     c_cc[NCCS];   /* special characters */

};
#endif 

    memset(&term, 0, sizeof(struct termios));

    if ((cfsetispeed(&term, B9600) < 0) ||
        (cfsetospeed(&term, B9600) < 0)) {
            perror("Unable to set baudrate");
    }

    /*
    CREAD - включить прием
    CLOCAL - игнорировать управление линиями с помошью
    */
    term.c_cflag |= (CREAD | CLOCAL);
    /* CSIZE - маска размера символа */
    term.c_cflag &= ~CSIZE;
    /* CS8 - 8 битные символы */
    term.c_cflag |= CS8;

    /* CSTOPB - при 1 - два стоп бита, при 0 - один */
    term.c_cflag &= ~CSTOPB;

    /*
    ICANON - канонический режим
    ECHO - эхо принятых символов
    ECHOE - удаление предыдущих символов по ERASE, слов по WERASE
    ISIG - реагировать на управляющие символы остановки, выхода, прерывания
    */
    term.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG);
    /* INPCK - вкл. проверку четности */
    term.c_iflag &= ~(INPCK);
    /* OPOST - режим вывода по умолчанию */
    term.c_oflag &= ~OPOST;

    /*
    TCSANOW - примернить изменения сейчасже
    TCSADRAIN - применить после передачи всех текущих данных
    TCSAFLUSH - приемнить после окончания передачи, все принятые но не считанные данные очистить
    */
    if (tcsetattr(fd, TCSANOW, &term) < 0)
    {
        perror("Unable to set port parameters");     
    }

  memset(tempBuf,0x00,sizeof(tempBuf));
  memset(buf,0x00,sizeof(buf));
      do{
          
           res = read(fd,buf,512);
           if (res > 0) {
              for (countBuf = 0; countBuf  < res; countBuf++){
                if(countTempBuf > 511) {
                 printf("out of array tempBuf \n"); 
                 std::exit(-1);
                }
                //printf("check \n"); 
               tempBuf[countTempBuf] = buf[countBuf];
               countTempBuf++;
              }
              
            }
            else {
                if( countTempBuf >= numByte){

                  printf("Read %d bytes:\n", countTempBuf);
                  for (countBuf = 0; countBuf < countTempBuf; countBuf ++){
                    printf("%02x ", tempBuf[countBuf]);
                  }
                  printf("\n");
                  do{
                    for (int i = 0; i < 10; i++){
                      usleep(10000); 
                      res = read(fd,buf,512);
                    }
                  
                  }while (res != 0);
                  countTempBuf = 0;
                  memset(tempBuf,0x00,sizeof(tempBuf));
                  memset(buf,0x00,sizeof(buf));
                }
                
              
            }
        usleep(1500); 
        }while (1);
}
