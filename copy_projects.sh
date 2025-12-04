#!/bin/bash
echo "开始复制Keil工程文件..."

# 源文件夹路径
SOURCE="D:/Desktop/KeilProject"

# 检查源文件夹是否存在
if [ ! -d "$SOURCE" ]; then
    echo "❌ 源文件夹不存在: $SOURCE"
    exit 1
fi

echo "源文件夹: $SOURCE"

# 定义复制函数：只复制需要的文件
copy_project() {
    local source_dir="$1"
    local target_dir="$2"
    
    echo "正在复制: $source_dir -> $target_dir"
    
    # 1. 先清理目标文件夹（保留README.md）
    if [ -d "$target_dir" ]; then
        find "$target_dir" -type f ! -name "README.md" -delete 2>/dev/null
        find "$target_dir" -type d \( -name "Objects" -o -name "Listings" -o -name "OBJ" -o -name "LISTING" \) -exec rm -rf {} + 2>/dev/null
    fi
    
    # 2. 复制所有.c和.h文件
    find "$source_dir" -maxdepth 1 -type f \( -name "*.c" -o -name "*.h" \) -exec cp {} "$target_dir/" \; 2>/dev/null
    
    # 3. 复制工程文件（可选）
    cp "$source_dir"/*.uvproj "$target_dir/" 2>/dev/null || true
    
    # 4. 复制常用文件夹（如果存在）
    for subdir in CORE HARDWARE User Libraries Inc Src; do
        if [ -d "$source_dir/$subdir" ]; then
            cp -r "$source_dir/$subdir" "$target_dir/"
            echo "  复制子目录: $subdir"
        fi
    done
    
    # 5. 复制其他可能的文件
    for ext in txt md pdf; do
        cp "$source_dir"/*.$ext "$target_dir/" 2>/dev/null || true
    done
    
    echo "  ✅ 完成"
}

# 开始复制各个项目
copy_project "$SOURCE/2-1 点亮LED" "01-2-1点亮LED"
copy_project "$SOURCE/3-1 独立按键控制LED" "02-3-1独立按键控制LED"
copy_project "$SOURCE/3-2 独立按键控制取反" "03-3-2独立按键控制取反"
copy_project "$SOURCE/5-1 模块化编程" "04-5-1模块化编程"
copy_project "$SOURCE/5-2 LCD1602调试工具" "05-5-2LCD1602调试工具"
copy_project "$SOURCE/6-1 矩阵键盘" "06-6-1矩阵键盘"
copy_project "$SOURCE/7-1 按键控制LED" "07-7-1按键控制LED"
copy_project "$SOURCE/7-2 定时器时钟" "08-7-2定时器时钟"
copy_project "$SOURCE/7-3 定时器流水灯" "09-7-3定时器流水灯"
copy_project "$SOURCE/8-1 串口向电脑发送" "10-8-1串口向电脑发送"
copy_project "$SOURCE/8-2 电脑用串口控制" "11-8-2电脑用串口控制"
copy_project "$SOURCE/8-3 UART的实际应用" "12-8-3UART的实际应用"
copy_project "$SOURCE/11-1 蜂鸣器播放提示音" "13-11-1蜂鸣器播放提示音"
copy_project "$SOURCE/13-1 DS18B20温度读取" "14-13-1DS18B20温度读取"
copy_project "$SOURCE/15-1 LED呼吸灯" "15-15-1LED呼吸灯"
copy_project "$SOURCE/15-2 电机PWM" "16-15-2电机PWM"
copy_project "$SOURCE/EEPROM" "17-EEPROM"

echo "✅ 所有工程文件复制完成！"
