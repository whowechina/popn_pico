# Popn Pico - Pop'n Music 风格的迷你控制器
[Click here for the English version of this guide.](README.md)

<img src="doc/main.jpg" width="70%">

我制作了两代 Popn Pico。最新的是 Popn Pico 2。它比第一代要大一些。

本文档是关于最新一代的。第一代的文件被存档在 `Gen1Archive` 文件夹中。这是第一代的样子。
<img src="Gen1Archive/doc/main.jpg" width="60%">

## 特性
* 使用了自制的 40mm 圆顶按钮。
* 完整的 HID 灯光支持。
* 命令行配置。
* 所有源文件开放。

感谢许多尊敬的爱好者和公司将他们的工具或材料免费或开源（KiCad，OnShape，InkScape，Raspberry 相关工具, 嘉立创，等）。

特别感谢社区项目和开发者的帮助，还有如下项目：
* RP_Silicon_KiCad: https://github.com/HeadBoffin/RP_Silicon_KiCad
* Type-C: https://github.com/ai03-2725/Type-C.pretty

## 关于许可证
它是 CC-NC 授权。所以你只能给自己和或者免费给你的朋友 DIY，不能利用这个项目赚钱，比如收费的代做，出售整机等，连源作者都不敢提的抄袭或者稍微改改换个名字来打擦边球就更不可以了。注意团购和拼单订购原始元器件是合理的，非盈利的方式卖掉剩余的元器件也是可以接受的。

如果希望找我购买成品或者寻求商用授权，请联系我（Discord，QQ 群，闲鱼，微信群或者在 issue 区留下你的联系方式）。

## 我的 Discord 服务器邀请
https://discord.gg/M8f2PPQFEA

## 其他项目
你也可以查看我其他的酷炫项目。

<img src="https://github.com/whowechina/popn_pico/raw/main/doc/main.jpg" height="100px"> <img src="https://github.com/whowechina/iidx_pico/raw/main/doc/main.jpg" height="100px"> <img src="https://github.com/whowechina/iidx_teeny/raw/main/doc/main.jpg" height="100px"> <img src="https://github.com/whowechina/chu_pico/raw/main/doc/main.jpg" height="100px"> <img src="https://github.com/whowechina/mai_pico/raw/main/doc/main.jpg" height="100px"> <img src="https://github.com/whowechina/diva_pico/raw/main/doc/main.jpg" height="100px"> <img src="https://github.com/whowechina/aic_pico/raw/main/doc/main.gif" height="100px"> <img src="https://github.com/whowechina/groove_pico/raw/main/doc/main.gif" height="100px">  <img src="https://github.com/whowechina/geki_pico/raw/main/doc/main.jpg" height="100px"> <img src="https://github.com/whowechina/musec_pico/raw/main/doc/main.jpg" height="100px"> <img src="https://github.com/whowechina/ju_pico/raw/main/doc/main.jpg" height="100px"> <img src="https://github.com/whowechina/popn_pico/raw/main/doc/main.jpg" height="100px">

* Popn Pico: https://github.com/whowechina/popn_pico
* IIDX Pico: https://github.com/whowechina/iidx_pico
* IIDX Teeny: https://github.com/whowechina/iidx_teeny
* Chu Pico: https://github.com/whowechina/chu_pico
* Mai Pico: https://github.com/whowechina/mai_pico
* Diva Pico: https://github.com/whowechina/diva_pico
* AIC Pico: https://github.com/whowechina/aic_pico
* Groove Pico: https://github.com/whowechina/groove_pico
* Geki Pico: https://github.com/whowechina/geki_pico
* Musec Pico: https://github.com/whowechina/musec_pico
* Ju Pico: https://github.com/whowechina/ju_pico
* Bishi Pico: https://github.com/whowechina/bishi_pico

## **声明** ##
我在个人业余时间内制作了这个项目，并将继续改进这个项目。我已尽我所能确保所有内容的准确性和功能性，但总有可能出现错误。如果你因使用这个开源项目而造成时间或金钱的损失，我不能负责。感谢你的理解。

## 如何制作
### PCB 和元器件
* 去 JLCPCB 或者其他 PCB 供应商下单，使用最新的 `Production\PCB\popn_pico2_xxx.zip` gerber 文件，选择常规 FR-4 板材，黑色，**1.6mm** 厚度.
* 1x Rasberry Pico Pi Pico 或者兼容的克隆板。  
  https://www.raspberrypi.com/products/raspberry-pi-pico
* 3x USB Type-C 插座 (918-418K2023S40001 或 KH-TYPE-C-16P)。
* 27x WS2812B-3528 RGB LED。
* 9x WS2812B-4020 RGB LEDs (侧面发光)。
* 6x 0603 0.1uF 电容 (0.1~1uF all 都可以)。
* 2x 0603 5.1kohm 电阻。
* 9x 凯华 Choc v2 轴，线性，35-50gf 力度最佳，我自己用凯华的白雨轴。
* 2x ALPS SKHHLWA010 6\*6\*7mm 或者兼容的轻触开关。  
  https://tech.alpsalpine.com/e/products/detail/SKHHLWA010/

* 焊接完成后的效果。  
  <img src="doc/pcb1.jpg" width="90%">  
  <img src="doc/pcb2.jpg" width="90%">

* 注意这两个引脚的焊接，很容易疏忽，要么忘记焊，要么在过程中留下气泡。为了避免这种情况，从孔的一侧开始慢慢焊接，要用尽量少的焊丝和较多的助焊剂。  
  <img src="doc/usb_txrx.jpg" width="60%">

### 测试 PCB
* 现在你可以测试 PCB 了，把固件烧录进去。
* LED 都应该亮起并且按钮按下后有响应。
* Popn Pico 2 应该被识别为 USB HID 设备，这里是测试页面。  
  https://greggman.github.io/html5-gamepad-test/


### 3D 打印
#### 打印参数
* PLA 或 PETG.
* 层高: 0.2mm.
* 墙: >= 3.
* 支撑: 需要，仅在热床上生成，没必要为桥接支撑。
* 热床上涂胶水: 是的，可以防止脚部翘曲。
* 文件都是以毫米为单位，不是英寸。

#### 外壳部件
* 基座: `Production\3DPrint\popn_pico2_base.stl`. 颜色你自己选。可以使用特殊支撑材料以获得更好的螺丝孔表面。
* 中框: `Production\3DPrint\popn_pico2_support.stl`, 透明。
* 面板: `Production\3DPrint\popn_pico2_panel.3mf`. 建议使用多色打印系统，这样你就能为每个子部分选择不同的颜色。

#### 9x 按钮座
* Button Seat: `Production\3DPrint\popn_pico2_button_seat.stl`, 白色，倒过来打印。

### 组装
#### 需要的其他部件
* 9x 40mm 直径的透明塑料小球，一般用于圣诞树装饰。一般是由两个半边组成，我们只需要矮的半边。
  https://www.amazon.com/Plastic-Fillable-Ornaments-Acrylic-Christmas/dp/B09ZTSGL28/
* 8x **M3\*12mm 螺丝** 用于固定外壳。
* 8x 底部硅胶防滑垫（12mm 直径）。
* 透明软性胶或者 UV 固化胶。警告：避免使用任何氰基胶，比如 502 胶。任何有类似气味的胶也要避免，因为它们会在亚克力上留下白色雾化痕迹。

#### Steps
1. 我们先做 9 个圆形按钮。先把透明塑料小球的矮半边用之前提到的胶水粘到按钮座上。  
   <img src="doc/dome_button.jpg" width="70%">
2. 把 9 个圆形按钮安装到轴体上。
5. 把 PCB 放入基座，放上中框，最后放上面板，用螺丝把它们固定，在底部螺丝正上方放上防滑垫。

#### 注意事项
* 每台 3D 打印机和打印材料都有自己的公差。如果你发现按钮上的十字孔太紧，可以用针或刀片稍微扩大一下。
* 螺丝很容易把 3D 打印部件弄坏。所以拧的时候要非常慢，不要拧太紧。感觉到阻力突然增大时就要特别小心了。

### 固件
* UF2 文件在 `Production\Firmware` 文件夹中。
* 对于首次烧录，按住 BOOTSEL 按钮连接到 USB，会出现一个名为 "RPI-RP2" 的磁盘。将 UF2 固件二进制文件拖入其中。Popn Pico 2 的底部有一个小孔，它正对着 BOOTSEL 按钮。
* 如果已经烧录过 Popn Pico 2 固件，你可以使用命令行中的 "update" 或者在插入 USB 的时候按住至少 4 个按钮来进入更新模式。
* 要访问命令行，你可以使用这个 Web 串口终端连接到 Popn Pico 2 的命令行串口。（注意："?" 是帮助）  
  https://googlechromelabs.github.io/serial-terminal/

### 使用
* 非常简单。只要插上就可以玩了。

## CAD Source File
我使用的是 OnShape 的免费订阅。它很强大，但不能将原始设计存档到本地，所以我只能在这里分享链接。STL/DXF/DWG 文件是从这个在线文档导出的。
  https://cad.onshape.com/documents/fcfa3f71e200593febd1451f/w/3452f2d9fccae7d99b53d89a/e/55b4cd1b258679099c74739b
