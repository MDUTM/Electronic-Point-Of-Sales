# 电子点餐平台
## 描述
- 基于ARM平台(GEC6818)
- 该平台分为客户端为服务端（后台）； 客户端部署在ARM开发板，服务端部署在pc机
- 本平台使用Linux + ARM

## 编译
- 执行  
    ```make```
- 执行完后会在build目录生成  
    ```main epos server```

## 移植
- 把 `server` 部署在服务端
- 把 `main epos res/` 部署在开发板（嵌入式设备）
- `main` 是无欢迎界面的程序， `epos` 是有欢迎界面的程序
