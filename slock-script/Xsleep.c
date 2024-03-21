#include <stdlib.h>
#include <unistd.h>

int main() {
  // 设置屏幕保护和 DPMS 参数
  system("xset s on");
  system("xset +dpms");
  system("xset dpms 9 9 9");

  sleep(1);
  // 启动 slock 锁屏程序
  system("slock &");
  sleep(1);

  // 进入睡眠状态
  system("systemctl suspend");

  // 初始化变量
  int var = 0;

  // 检测 slock 是否还在运行
  while (1) {
    sleep(8);
    if (system("pgrep -x slock > /dev/null") == 0) {
      // 当达到 3 次时执行睡眠指令
      if (var == 3) {
        system("systemctl suspend");
        var = 0;
      } else {
        var++; // 自增变量
      }
    } else {
      // 重新设置 DPMS 参数
      system("xset dpms 600 600 600");
      break;
    }
  }

  return 0;
}
