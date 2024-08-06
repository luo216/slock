#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  // 检查是否提供了足够的参数
  if (argc != 2) {
    printf("Usage: %s <timeout>\n", argv[0]);
    return 1;
  }

  // 将字符串转换为整数
  unsigned int timeout = atoi(argv[1]) * 60;

  // 设置屏幕保护和 DPMS 参数
  system("xset s on");
  system("xset +dpms");
  system("xset dpms 10 10 10");

  // 启动 slock 锁屏程序
  system("pkill picom");
  system("slock &");
  sleep(1);

  // 初始化变量
  int var = 0;

  // 检测 slock 是否还在运行
  while (1) {
    sleep(1);
    if (system("pgrep -x slock > /dev/null") == 0) {
      // 当达到 timeout 次时执行睡眠指令
      if (var == timeout) {
        system("systemctl suspend");
        var = 0;
      } else {
        var++; // 自增变量
      }
    } else {
      // 重新设置 DPMS 参数
      system("xset dpms 600 600 600");
      system("picom &");
      system("setxkbmap -option 'caps:super'");
      break;
    }
  }

  return 0;
}
