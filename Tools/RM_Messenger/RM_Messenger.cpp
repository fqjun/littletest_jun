#include "include/RM_Messenger.hpp"

RM_Messenger::RM_Messenger(const Messenger_Config& _messenger_config)
    : messneger_cfg(_messenger_config)
{
}

#ifdef DEBUG_MESSENGER
/**
 * @brief 更新串口接收数据
 */
void RM_Messenger::updateReceiveInformation(const unsigned char* receive_arr)
{
    //转换类型为 int
    for (size_t i = 0; i < sizeof(transform_arr) / sizeof(transform_arr[0]); ++i) {
        this->transform_arr[i] =
            receive_arr[i + 1] - '0';  //需要 - '0',因为char转int会剩下ascII码的值
    }

    /* 1 更新颜色信息　update color */
    switch (transform_arr[0]) {
        case RED:
            this->receive_info.my_color = RED;
            break;
        case BLUE:
            this->receive_info.my_color = BLUE;
            break;
        default:
            this->receive_info.my_color = ALL_COLOR;
            break;
    }

    /* 2 更新模式信息 update mode */
    switch (transform_arr[1]) {
        case SUP_SHOOT:
            this->receive_info.now_run_mode = SUP_SHOOT;
            break;
        case ENERGY_AGENCY:
            this->receive_info.now_run_mode = ENERGY_AGENCY;
            break;
        case SENTRY_MODE:
            this->receive_info.now_run_mode = SENTRY_MODE;
            break;
        case BASE_MODE:
            this->receive_info.now_run_mode = BASE_MODE;
            break;
        default:
            this->receive_info.now_run_mode = SUP_SHOOT;
            break;
    }

    /* 3 更新当前机器人ID update Robot ID */
    switch (transform_arr[2]) {
        case HERO:
            this->receive_info.my_robot_id = HERO;
            break;
        case ENGINEERING:
            this->receive_info.my_robot_id = ENGINEERING;
            break;
        case INFANTRY:
            this->receive_info.my_robot_id = INFANTRY;
            break;
        case UAV:
            this->receive_info.my_robot_id = UAV;
            break;
        case SENTRY:
            this->receive_info.my_robot_id = SENTRY;
            break;
        default:
            this->receive_info.my_robot_id = INFANTRY;
            break;
    }

    /* 4 5 6 7 更新陀螺仪的yaw角度值 */
    //  TODO待修改bug
    // for (size_t i : this->receive_info.IMU_Yaw_Angle_Info.arr_Yaw_angle) {
    for (size_t i = 0; i < sizeof(this->receive_info.IMU_Yaw_Angle_Info.arr_Yaw_angle);++i) {
        // +4是接收串口数组中陀螺仪yaw角度值的起始位置
        this->receive_info.IMU_Yaw_Angle_Info.arr_Yaw_angle[i] = receive_arr[i + 4] - '0';
        // TODO：清除特别小的数字出现 e-10
    }

    /*8 9 10 11 更新陀螺仪的pitch角度值 */
    for (size_t i = 0; i < sizeof(this->receive_info.IMU_Pitch_Angle_Info.arr_Pitch_angle);++i) {
        // +4是接收串口数组中陀螺仪pitch角度值的起始位置
        this->receive_info.IMU_Pitch_Angle_Info.arr_Pitch_angle[i] = receive_arr[i + 8] - '0';
    }

    // for(int i = 0;i<=4;++i){
    //     this->receive_info.IMU_Pitch_Angle_Info.arr_Pitch_angle[i] = this->receive_arr[i + 8];
    // }

    // pitch_test = ((receive_arr[8]<<32) | (receive_arr[9]<<16)|(receive_arr[10]<<8)|(receive_arr[11]));
    // pitch_test = ((receive_arr[11]<<32) | (receive_arr[10]<<16)|(receive_arr[9]<<8)|(receive_arr[8]));
    
    // this->receive_info.IMU_Pitch_Angle_Info.arr_Pitch_angle[0] = '\000';
    // this->receive_info.IMU_Pitch_Angle_Info.arr_Pitch_angle[1] = '\000';
    // this->receive_info.IMU_Pitch_Angle_Info.arr_Pitch_angle[2] = '\000';
    // this->receive_info.IMU_Pitch_Angle_Info.arr_Pitch_angle[3] = '\000';

    // this->receive_info.IMU_Pitch_Angle_Info.arr_Pitch_angle[0] = this->receive_arr[8];
    // this->receive_info.IMU_Pitch_Angle_Info.arr_Pitch_angle[1] = this->receive_arr[9];
    // this->receive_info.IMU_Pitch_Angle_Info.arr_Pitch_angle[2] = this->receive_arr[10];
    // this->receive_info.IMU_Pitch_Angle_Info.arr_Pitch_angle[3] = this->receive_arr[11];

#ifdef DEBUG_MESSENGER
    this->receive_info.IMU_angle.IMU_angle_arr[0] = receive_arr[4];
    this->receive_info.IMU_angle.IMU_angle_arr[1] = receive_arr[5];
    this->receive_info.IMU_angle.IMU_angle_arr[2] = receive_arr[6];
    this->receive_info.IMU_angle.IMU_angle_arr[3] = receive_arr[7];
    this->receive_info.IMU_angle.IMU_angle_arr[4] = receive_arr[8];
    this->receive_info.IMU_angle.IMU_angle_arr[5] = receive_arr[9];
    this->receive_info.IMU_angle.IMU_angle_arr[6] = receive_arr[10];
    this->receive_info.IMU_angle.IMU_angle_arr[7] = receive_arr[11];
#endif

    cout << "receive_arr 8~11:" << static_cast<int>(receive_arr[8]) << " "
         << static_cast<int>(receive_arr[9]) << " " << static_cast<int>(receive_arr[10]) << " "
         << static_cast<int>(receive_arr[11]) << " " << endl;

    /* 12 13 更新陀螺仪的角加速度值 */
    this->receive_info.acceleration =
        SerialPort::mergeIntoBytes(receive_arr[12], receive_arr[13]) / 100.f;
    // fps_messenger->getTick();
    // TODO：清除123.36的出现,得读取当前 8 9 的内容才能排查

    /* 14 更新子弹速度 */
    this->transform_arr[3] = receive_arr[14] - '0';
    switch (this->transform_arr[3]) {
        case 1:
            this->receive_info.volacity_level = 15;
            break;
        case 2:
            this->receive_info.volacity_level = 18;
            break;
        case 3:
            this->receive_info.volacity_level = 30;
            break;
        default:
            this->receive_info.volacity_level = 15;
            break;
    }

    if (this->messneger_cfg.SHOW_SERIAL_INFORMATION == 0) {
        cout << "color:" << this->receive_info.my_color
             << " model:" << this->receive_info.now_run_mode
             << " ID:" << this->receive_info.my_robot_id
             << " yaw:" << this->receive_info.IMU_angle.Yaw_Angle/* this->receive_info.IMU_Yaw_Angle_Info.IMU_Yaw_angle */ << " pitch:"
             << this->receive_info.IMU_angle.Pitch_Angle/* pitch_test */ /* this->receive_info.IMU_Pitch_Angle_Info.IMU_Pitch_angle */
             << " acceleration:" << this->receive_info.acceleration
             << " volacity:" << this->receive_info.volacity_level << endl;
        cout << "------------------" << endl;
    }
    // fps_messenger->calculateFPS();
}
#else
/**
 * @brief 更新串口接收数据
 */
void RM_Messenger::updateReceiveInformation()
{
    //转换类型为 int
    for (size_t i = 0; i < sizeof(transform_arr) / sizeof(transform_arr[0]); ++i) {
        this->transform_arr[i] =
            this->receive_arr[i + 1] - '0';  //需要 - '0',因为char转int会剩下ascII码的值
    }

    /* 1 更新颜色信息　update color */
    switch (transform_arr[0]) {
        case RED:
            this->receive_info.my_color = RED;
            break;
        case BLUE:
            this->receive_info.my_color = BLUE;
            break;
        default:
            this->receive_info.my_color = ALL_COLOR;
            break;
    }

    /* 2 更新模式信息 update mode */
    switch (transform_arr[1]) {
        case SUP_SHOOT:
            this->receive_info.now_run_mode = SUP_SHOOT;
            break;
        case ENERGY_AGENCY:
            this->receive_info.now_run_mode = ENERGY_AGENCY;
            break;
        case SENTRY_MODE:
            this->receive_info.now_run_mode = SENTRY_MODE;
            break;
        case BASE_MODE:
            this->receive_info.now_run_mode = BASE_MODE;
            break;
        default:
            this->receive_info.now_run_mode = SUP_SHOOT;
            break;
    }

    /* 3 更新当前机器人ID update Robot ID */
    switch (transform_arr[2]) {
        case HERO:
            this->receive_info.my_robot_id = HERO;
            break;
        case ENGINEERING:
            this->receive_info.my_robot_id = ENGINEERING;
            break;
        case INFANTRY:
            this->receive_info.my_robot_id = INFANTRY;
            break;
        case UAV:
            this->receive_info.my_robot_id = UAV;
            break;
        case SENTRY:
            this->receive_info.my_robot_id = SENTRY;
            break;
        default:
            this->receive_info.my_robot_id = INFANTRY;
            break;
    }

    /* 4 5 6 7 更新陀螺仪的yaw角度值 */
    //  TODO待修改bug
    // for (size_t i : this->receive_info.IMU_Yaw_Angle_Info.arr_Yaw_angle) {
    for (size_t i = 0; i < sizeof(this->receive_info.IMU_Yaw_Angle_Info.arr_Yaw_angle);++i) {
        // +4是接收串口数组中陀螺仪yaw角度值的起始位置
        this->receive_info.IMU_Yaw_Angle_Info.arr_Yaw_angle[i] = this->receive_arr[i + 4];
        // TODO：清除特别小的数字出现 e-10
    }

    /*8 9 10 11 更新陀螺仪的pitch角度值 */
    for (size_t i = 0;
         i < sizeof(this->receive_info.IMU_Pitch_Angle_Info.arr_Pitch_angle);++i) {
        // +4是接收串口数组中陀螺仪pitch角度值的起始位置
        this->receive_info.IMU_Pitch_Angle_Info.arr_Pitch_angle[i] = this->receive_arr[i + 8];
    }

    // for(int i = 0;i<=4;++i){
    //     this->receive_info.IMU_Pitch_Angle_Info.arr_Pitch_angle[i] = this->receive_arr[i + 8];
    // }

    // pitch_test = ((receive_arr[8]<<32) | (receive_arr[9]<<16)|(receive_arr[10]<<8)|(receive_arr[11]));
    // pitch_test = ((receive_arr[11]<<32) | (receive_arr[10]<<16)|(receive_arr[9]<<8)|(receive_arr[8]));
    
    // this->receive_info.IMU_Pitch_Angle_Info.arr_Pitch_angle[0] = '\000';
    // this->receive_info.IMU_Pitch_Angle_Info.arr_Pitch_angle[1] = '\000';
    // this->receive_info.IMU_Pitch_Angle_Info.arr_Pitch_angle[2] = '\000';
    // this->receive_info.IMU_Pitch_Angle_Info.arr_Pitch_angle[3] = '\000';

    // this->receive_info.IMU_Pitch_Angle_Info.arr_Pitch_angle[0] = this->receive_arr[8];
    // this->receive_info.IMU_Pitch_Angle_Info.arr_Pitch_angle[1] = this->receive_arr[9];
    // this->receive_info.IMU_Pitch_Angle_Info.arr_Pitch_angle[2] = this->receive_arr[10];
    // this->receive_info.IMU_Pitch_Angle_Info.arr_Pitch_angle[3] = this->receive_arr[11];

    cout << "receive_arr 8~11:" << static_cast<int>(receive_arr[8]) << " "
         << static_cast<int>(receive_arr[9]) << " " << static_cast<int>(receive_arr[10]) << " "
         << static_cast<int>(receive_arr[11]) << " " << endl;

    /* 12 13 更新陀螺仪的角加速度值 */
    this->receive_info.acceleration =
        SerialPort::mergeIntoBytes(this->receive_arr[12], this->receive_arr[13]) / 100.f;
    // fps_messenger->getTick();
    // TODO：清除123.36的出现,得读取当前 8 9 的内容才能排查

    /* 14 更新子弹速度 */
    this->transform_arr[3] = this->receive_arr[14] - '0';
    switch (this->transform_arr[3]) {
        case 1:
            this->receive_info.volacity_level = 15;
            break;
        case 2:
            this->receive_info.volacity_level = 18;
            break;
        case 3:
            this->receive_info.volacity_level = 30;
            break;
        default:
            this->receive_info.volacity_level = 15;
            break;
    }

    if (this->messneger_cfg.SHOW_SERIAL_INFORMATION == 1) {
        cout << "color:" << this->receive_info.my_color
             << " model:" << this->receive_info.now_run_mode
             << " ID:" << this->receive_info.my_robot_id
             << " yaw:" << this->receive_info.IMU_Yaw_Angle_Info.IMU_Yaw_angle << " pitch:"
             << /* pitch_test */ this->receive_info.IMU_Pitch_Angle_Info.IMU_Pitch_angle
             << " acceleration:" << this->receive_info.acceleration
             << " volacity:" << this->receive_info.volacity_level << endl;
        cout << "------------------" << endl;
    }
    // fps_messenger->calculateFPS();
}
#endif

/**
 * @brief 返回串口接收数组
 * @return unsigned*
 */
unsigned char* RM_Messenger::getReceiveArray()
{
    #ifdef DEBUG_MESSENGER
    #else
    return this->receive_arr;
    #endif
}

Receive_Info RM_Messenger::getReceiveInfo()
{
    return this->receive_info;
}

Send_Info& RM_Messenger::getSendInfo()
{
    return this->send_info;
}
