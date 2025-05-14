//
//  MSDKIOTDevice.h
//  MSDKIOT
//
//  Created by lsqMacbook Pro        on 2025/2/14.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import "MSDKDeviceCommandModel.h"

@class MSDKIOTDevice;

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(NSInteger, MSDKIOTDeviceConnectSessionStatus) {
    MSDKIOTDeviceConnectSessionStatus_Unknown,
    MSDKIOTDeviceConnectSessionStatus_Connecting,                              //连接中
    MSDKIOTDeviceConnectSessionStatus_ConnectFailed,                           //连接失败
    MSDKIOTDeviceConnectSessionStatus_Connected,                               //连接成功
    MSDKIOTDeviceConnectSessionStatus_ConnectClosed,                           //session已被关闭
};

typedef NS_ENUM(NSInteger, MSDKIOTDeviceCardStatus) {
    MSDKIOTDeviceCardStatus_Remove = 0,                 // 无卡
    MSDKIOTDeviceCardStatus_Error,                     // 卡错误
    MSDKIOTDeviceCardStatus_Unkonw,                       // 卡未知格式
    MSDKIOTDeviceCardStatus_Unsupported,                // 卡不支持格式
    MSDKIOTDeviceCardStatus_Uninit,                 // 卡未初始化
    MSDKIOTDeviceCardStatus_Ok,                        // 卡正常
};

typedef enum  FILELISTTYPE
{
    FILELISTTYPE_MOVIE = 0,    // 视频文件
    FILELISTTYPE_PHOTO,       // 照片文件
    FILELISTTYPE_EMR,         // 紧急文件
} FILELISTTYPE;

typedef enum  ENUM_MODE
{
    TCICCHGMODE_MOVIE= 0, // movie模式
    TCICCHGMODE_PHOTO,    // photo模式
    TCICCHGMODE_PBK,      // playback模式
} ENUMMODE;

typedef enum  CONNECT_STATUS
{
    DISCONNECT= 0,
    CONNECT_WIFI,
    CONNECT_4G,
    CONNECT_ALL
} CONNECT_STATUS;

typedef enum  ACC_STATUS
{
    ACC_OFF= 0,
    ACC_ON,
} ACC_STATUS;

@protocol MSDKIOTDeviceDelegate <NSObject>

@optional

// 连接状态
- (void)camera:(MSDKIOTDevice *)device connectSessionStatusChanged:(MSDKIOTDeviceConnectSessionStatus)status;

// 实时流画面
- (void)camera:(MSDKIOTDevice *)device didPlayCameraLiveVideo:(UIImage *)image channel:(int)channel;

// SD卡视频画面
- (void)camera:(MSDKIOTDevice *)device didPlayCameraSDCardVideo:(UIImage *)image utcTimeStamp:(NSInteger)utcTimeStamp;

// 录像时间
- (void)camera:(MSDKIOTDevice *)device didRecordWithRecordSecond:(NSInteger)second;

// 录像结束
- (void)camera:(MSDKIOTDevice *)device didStopRecordWithRecordFilePath:(NSString * _Nonnull)filePath;

// 直播流更新速率 bitRate: 字节每秒（B）frameRate: 帧每秒
- (void)camera:(MSDKIOTDevice *)device didLiveVideoBpsUpdateWithBitRate:(unsigned int)bitRate frameRate:(unsigned int)frameRate;

// sd播放器缓存开始--实时播放
- (void)didReceiveSdVideoCacheStart;

// sd播放器缓存结束--实时播放
- (void)didReceiveSdVideoCacheEnd;

// sd直播播完
- (void)cameraSdVideoEnd;

@end


@interface MSDKIOTDevice : NSObject


@property (nonatomic, weak) id<MSDKIOTDeviceDelegate> delegate;

@property (nonatomic, assign) MSDKIOTDeviceConnectSessionStatus sessionStatus;

// 连接设备
- (void)connectDeviceWithLicense:(NSString *)license result:(void(^_Nullable)(MSDKIOTDeviceConnectSessionStatus state))result;

// 断开设备连接
- (void)disConnectDevice;

// 打开预览
- (void)openPreview:(int)channel audio:(BOOL)audio;

// 关闭预览
- (void)closePreview:(int)channel audio:(BOOL)audio;

// 获取录像状态
- (void)getRecordStatus:(void(^)(NSInteger status))successBlock failuerBlock:(void(^)(void))failuerBlock;

// 设置设备录像状态
- (void)setRecordStatus:(NSInteger)status successBlock:(void(^)(NSInteger result))successBlock failuerBlock:(void(^)(void))failuerBlock;

// 远程拍照
- (void)snapshot:(void(^)(NSInteger result))successBlock failuerBlock:(void(^)(void))failuerBlock;

// 查询SD卡状态 0:EMMC, 1:EXTERNAL_SD
- (void)getSDCardStatus:(int)type successBlock:(void(^)(NSInteger MSDKIOTDeviceCardStatus))successBlock failuerBlock:(void(^)(void))failureBlock;

// 获取设备存储空间 0:EMMC, 1:EXTERNAL_SD
//successBlock：单位是Byte
- (void)getStorageSpace:(int)type successBlock:(void(^_Nonnull)(NSInteger free, NSInteger total))successBlock failuerBlock:(void(^)(void))failuerBlock;

// 格式化
- (void)formatCard:(void(^)(NSInteger result))successBlock failuerBlock:(void(^)(void))failuerBlock;

// 获取设备模式 0:movie, 1:photo, 2:playback
- (void)getMode:(void(^)(NSInteger mode))successBlock failuerBlock:(void(^)(void))failuerBlock;

// 获取设备模式 0:movie, 1:photo, 2:playback
- (void)changeMode:(int)mode successBlock:(void(^)(NSInteger result))successBlock failuerBlock:(void(^)(void))failuerBlock;

// 获取设备文件列表
// offset传入偏移量，从0开始；number：传入这次需要获取到的数量
- (void)getFileList:(FILELISTTYPE)type offset:(int)offset number:(int)number successBlock:(void(^_Nonnull)(NSMutableArray *fileArr))successBlock failuerBlock:(void(^)(void))failuerBlock;

// 设置视频回放的文件
- (void)setPlayFile:(NSString *_Nonnull)filePath result:(void(^_Nonnull)(NSInteger status))block failuerBlock:(void(^)(void))failuerBlock;

// 监听回放
- (void)openSdCardFileObserveEnable:(BOOL)open start:(void(^_Nonnull)(NSInteger startTime))startBlock end:(void(^_Nonnull)(NSInteger endTime))endBlock;

// 设置当前时间点的卡录像播放资源，timePoint：目前随便传
- (void)playDeviceSDCardRecordWithTimePoint:(NSString *)timePoint;

//  播放卡录像视频
- (void)startCameraSDCardPlay;

//  停止卡录像播放
- (void)stopCameraSDCardPlay;

/// 检查版本更新 1：FW，4：MCU
/// @param successBlock 成功   version：有数据表示有新固件
- (void)checkSoftwareUpdate:(int)type successBlock:(void(^)(NSString *version))successBlock failuerBlock:(void(^)(void))failuerBlock;

// 固件升级 1：FW，4：MCU
- (void)setSoftwareUpdate:(int)type successBlock:(void(^)(NSInteger result))successBlock failuerBlock:(void(^)(void))failuerBlock;

// 查询固件版本
- (void)getSoftwareVersion:(void(^)(NSString *fwVersion, NSString *MCUVersion))successBlock failuerBlock:(void(^)(void))failuerBlock;

// 文件加锁和解锁 status：1:加锁， 0：解锁
- (void)fileLockAndUnlock:(NSString *_Nonnull)filePath result:(void(^_Nonnull)(NSInteger status))block failuerBlock:(void(^)(void))failuerBlock;

// 预览加锁
- (void)previewLock:(void(^)(NSInteger result))successBlock failuerBlock:(void(^)(void))failuerBlock;

// 恢复出厂设置
- (void)restoreFactory:(void(^)(NSInteger result))successBlock failuerBlock:(void(^)(void))failuerBlock;

// 获取缩略图
- (void)getThumb:(NSString *_Nonnull)filePath result:(void(^_Nonnull)(UIImage *thumbImage))block failuerBlock:(void(^)(void))failuerBlock;

// 文件删除
- (void)deleteFile:(NSString *_Nonnull)filePath result:(void(^_Nonnull)(NSInteger status))block failuerBlock:(void(^)(void))failuerBlock;

// 获取某一路摄像头状态
// 入参为摄像头索引，从0开始
- (void)getCameraState:(int)index result:(void(^_Nonnull)(NSInteger status))block failuerBlock:(void(^)(void))failuerBlock;

// 下载照片
- (void)downloadPhoto:(NSString *_Nonnull)file progress:(void(^_Nonnull)(float progress))progressBlock successBlock:(void(^_Nonnull)(UIImage *photoImage))successBlock failuerBlock:(void(^)(void))failuerBlock;

// 获取设备的连接状态
- (void)getDeviceConnectStatus:(void(^)(CONNECT_STATUS result))successBlock failuerBlock:(void(^)(void))failuerBlock;

// 获取ACC状态，判断车有没有启动
- (void)getACCStatus:(void(^)(ACC_STATUS result))successBlock failuerBlock:(void(^)(void))failuerBlock;


@end



NS_ASSUME_NONNULL_END
