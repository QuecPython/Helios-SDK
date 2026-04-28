# mklfs 命令使用说明文档

## 概述

`mklfs` 是一个用于创建和管理 LittleFS 镜像的命令行工具。它支持创建、挂载、卸载和清理 LittleFS 镜像。

## 版本信息

当前版本：`mklfs 1.0.0`

## 使用方法

```
mklfs [命令] [选项]
```

## 命令

### make

创建一个 LittleFS 镜像。

#### 语法

```
mklfs make [选项]
```

#### 选项

- `-i, --image <image>`: 指定 LittleFS 镜像文件的路径。
- `-s, --block-size <block_size>`: 指定 LittleFS 镜像的块大小。
- `-c, --block-count <block_count>`: 指定 LittleFS 镜像的块数量。
- `-f, --lfs-format <lfs_format>`: 指定 LittleFS 镜像的格式。

> 说明：
> - `-f` 缺省时，默认值为 `2`，表示使用 LittleFS 2.0 格式。
> - `-i` 缺省时，使用的 LittleFS 镜像格式不同，默认值也不同：
>   - 使用 LittleFS 1.0 格式，默认值为 `lfs1.img`。
>   - 使用 LittleFS 2.0 格式，默认值为 `lfs2.img`。
> - `-s` 缺省时，默认值为 `4096`，表示每个块的大小为 4K。
> - `-c` 缺省时，默认值为 `128`，表示 LittleFS 镜像有 128 个块。


#### 示例

```
mklfs make -i myfs.img -s 4096 -c 1024 -f 2
```

### mount

挂载一个 LittleFS 镜像。

#### 语法

```
mklfs mount [选项]
```

#### 选项

- `-i, --image <image>`: 指定 LittleFS 镜像文件的路径。

#### 示例

```
mklfs mount -i myfs.img
```

### umount

卸载一个 LittleFS 镜像。

#### 语法

```
mklfs umount [选项]
```

#### 选项

- `-i, --image <image>`: 指定 LittleFS 镜像文件的路径。

#### 示例

```
mklfs umount -i myfs.img
```

### clean

清理一个 LittleFS 镜像。

#### 语法

```
mklfs clean [选项]
```

#### 选项

- `-i, --image <image>`: 指定 LittleFS 镜像文件的路径。

#### 示例

```
mklfs clean -i myfs.img
```

### help

显示帮助信息并退出。

#### 语法

```
mklfs help
```

## 版本信息

可以使用 `-v` 或 `--version` 参数来查看当前工具的版本信息。

#### 示例

```
mklfs --version
```

## 示例

- 创建一个 LittleFS 镜像：

  ```
  mklfs make -i myfs.img -s 4096 -c 1024 -f 2
  ```

- 挂载一个 LittleFS 镜像：

  ```
  mklfs mount -i myfs.img
  ```

- 卸载一个 LittleFS 镜像：

  ```
  mklfs umount -i myfs.img
  ```

- 清理一个 LittleFS 镜像：

  ```
  mklfs clean -i myfs.img
  ```

## 帮助

如需获取更多帮助信息，可以使用以下命令：

```
mklfs help
```

此命令将显示所有可用命令及其选项的详细信息。