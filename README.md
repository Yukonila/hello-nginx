# Webtext - Hello World HTTP Server

Linux C++ HTTP 服务，使用 `libmicrohttpd` 库实现，监听 8080 端口，返回 "Hello World"。

## 功能特性

- ✅ **简单 HTTP 服务**：基于 `libmicrohttpd` 实现
- ✅ **监听端口**：8080（仅本地访问）
- ✅ **返回内容**：`Hello World`（纯文本）
- ✅ **请求处理**：仅支持 GET 请求，其他方法返回 405

## 编译运行

### 安装依赖

```bash
# Arch Linux
sudo pacman -S libmicrohttpd

# Ubuntu/Debian
sudo apt install libmicrohttpd-dev
```

### 编译

```bash
mkdir build && cd build
cmake ..
make
```

### 运行

```bash
./Webtext
```

输出示例：
```
========================================
C++ HTTP Server started successfully!
Listening on: http://127.0.0.1:8080
Press Enter to stop the server...
========================================
```

### 测试

```bash
curl http://127.0.0.1:8080
# 输出: Hello World
```

## 配置 Nginx 反向代理

### 安装 Nginx

```bash
# Arch Linux
sudo pacman -S nginx

# Ubuntu/Debian
sudo apt install nginx
```

### 配置文件

编辑 `/etc/nginx/nginx.conf`，添加以下配置：

```nginx
http {
    # ... 其他配置 ...

    server {
        listen 80;
        server_name _;

        location / {
            proxy_pass http://127.0.0.1:8080;
            proxy_set_header Host $host;
            proxy_set_header X-Real-IP $remote_addr;
            proxy_set_header X-Forwarded-For $proxy_add_x_forwarded_for;
            proxy_set_header X-Forwarded-Proto $scheme;
        }
    }
}
```

### 重启 Nginx

```bash
# Arch Linux
sudo systemctl restart nginx

# Ubuntu/Debian
sudo systemctl restart nginx
```

### 测试

浏览器访问 `http://服务器IP`，应显示：

```
Hello World
```

## 技术实现

- **HTTP 服务**：使用 `libmicrohttpd` 库
- **监听地址**：`127.0.0.1:8080`（仅本地访问）
- **请求处理**：`MHD_start_daemon` + `handle_request` 回调函数
- **Nginx 反向代理**：`proxy_pass` 将 80 端口请求转发至 8080

## 依赖

- C++11
- `libmicrohttpd` 库

---

**作者**：Yukonila  
**创建时间**：2026-05-09