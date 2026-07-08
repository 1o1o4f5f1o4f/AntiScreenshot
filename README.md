# AntiScreenshot - 防截屏工具

简单的防截屏小工具，原来是做给自己凑合着用的，现在开源

## 原理

创建一个全屏、透明、置顶、鼠标可穿透的窗口，调用 WindowsAPI 的 `SetWindowDisplayAffinity`，把显示亲和性设成 `WDA_MONITOR`，使窗口在截屏时返回一片黑。

## 构建

构建：

```shell
mingw32-make
```

运行：

```shell
mingw32-make run
```

清理构建产物：

```shell
mingw32-make clean
```

## 注意事项

- 至少使用Windows8，否则会因为不支持 `WDA_MONITOR` 特性而无法运行。
- 该程序无法防止某些软件截图，例如用 `DXGI` 或 `DirectX` 接口的截图工具，可能会绕过去。
- 远程桌面环境不一定支持。
- **总之，该软件无法完全防止截屏，本程序不负任何责任。**

## 许可证

Copyright (C) 2026 1o1o4f5f1o4f

本项目基于 **GNU General Public License v3.0** 开源，详见 [LICENSE](LICENSE) 文件。

简而言之，你可以自由地使用、修改、分发本软件，但必须：
- 保留原版权声明
- 注明你做的修改
- 保持相同的 GPL-3.0 许可证开源
- 本软件不提供任何明示或暗示的担保，**作者不对使用本软件产生的任何后果负责**
