#pragma once
#include "../../../Basis/RM_Serial/include/RM_Serial.h"
#include "../../../Basis/RM_Control/Debug_Controller.h"
#include <stdint.h>

#define DEBUG_MESSENGER

typedef struct Receive_Information
{
    int   my_color;
    int   now_run_mode;
    int   serial_plan;
    int   armor_size;
    int   my_robot_id;
    float acceleration;

    union IMU_Yaw_Angle_Information
    {
        float   IMU_Yaw_angle ;
        uint8_t arr_Yaw_angle[4];
    } IMU_Yaw_Angle_Info;

    union IMU_Pitch_Angle_Information
    {
        float   IMU_Pitch_angle ;
        uint8_t arr_Pitch_angle[4];
    } IMU_Pitch_Angle_Info;

    union 
    {
      struct 
      {
        float Yaw_Angle;
        float Pitch_Angle;
      };
      uint8_t IMU_angle_arr[8];
    }IMU_angle;
    

    int volacity_level;
    /**
     * @brief   串口信息接收结构体
     * @param:  my_color          描述己方颜色信息
     * @param:  now_run_mode      描述运行模式信息
     * @param:  armor_size        描述装甲板尺寸信息
     * @param:  serial_plan       描述串口通讯方式信息//TODO未用上
     * @param:  my_robot_id       描述当前机器人ID信息
     * @param:  IMU_Yaw_Angle_Info    描述陀螺仪的yaw轴角度（有符号）
     * @param:  IMU_Pitch_Angle_Info    描述陀螺仪的pitch轴角度（有符号）
     * @param:  acceleration      描述陀螺仪角加速度 .00
     * @param:  volacity_level    描述当前机器人子弹速度
     */
} Receive_Info;

typedef struct Send_Information
{
    float angle_yaw;
    float angle_pitch;
    int   symbol_yaw;
    int   symbol_pitch;
    int   command;
    int   is_found_target;
    float depth;
    /**
     * @brief   串口信息发送结构体
     * @param:  angle_yaw         yaw 轴角度
     * @param:  angle_pitch       pitch 轴角度
     * @param:  symbol_yaw        yaw轴符号（右正左负）
     * @param:  symbol_pitch      pitch轴符号（下正上负）
     * @param:  command           机器人的开火指令：0->不开火 1->单发开火一枪 2->跟随 3->不跟随
     * @param:  is_found_target   是否发现目标：1->发现 0->未发现
     * @param:  depth             深度信息
     */

} Send_Info;

typedef struct Messenger_Config
{
    int SHOW_SERIAL_INFORMATION;
    Messenger_Config()
    {
        SHOW_SERIAL_INFORMATION = 0;
    }
} Messenger_Cfg;

// 数据传输
class RM_Messenger {
  public:
    // 初始化数据
    RM_Messenger(const Messenger_Config& _messenger_config);
    ~RM_Messenger(){};

  public:
    // 接受
    #ifdef DEBUG_MESSENGER
    void updateReceiveInformation(const unsigned char* receive_arr);
    #else
    void updateReceiveInformation();
    #endif
    // 返回串口接收数组
    unsigned char* getReceiveArray();
    // 获取接收数据
    Receive_Info getReceiveInfo();

  public:
    // 发送
    // 获取发送数据
    Send_Info& getSendInfo();

  private:
    Receive_Info receive_info;
    Send_Info    send_info;

  private:
    Messenger_Cfg messneger_cfg;

    int transform_arr[4];

#ifdef DEBUG_MESSENGER

#else
    unsigned char receive_arr[REC_BUFF_LENGTH];
#endif

#ifdef DEBUG_MESSENGER
  private:
    float pitch_test = 0.f;
#endif
};