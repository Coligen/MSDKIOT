//
//  MSDKCloudDeviceManager.h
//  MSDKIOT
//
//  Created by lsqMacbook Pro        on 2025/4/15.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import "MSDKCloudEventModel.h"


@class MSDKCloudDeviceManagerDelegate;

typedef NS_ENUM(NSInteger, MSDKCloudRecordOrderType) {
    MSDKCloudRecordOrderType_Desc,    //降序
    MSDKCloudRecordOrderType_Asce     //升序
};


@protocol MSDKCloudDeviceManagerDelegate <NSObject>

@optional

// 云端视频播放
// 播放回调
- (void)cloudDeviceManagerDidPlayDecoderVideoData:(UIImage *)image utcTimeStamp:(NSInteger)utcTimeStamp channel:(int)channel;

// 播放缓存开始回调
- (void)didReceiveCloudVideoCacheStart:(NSInteger)utcTimeStamp channel:(int)channel;

// 播放缓存结束回调
- (void)didReceiveCloudVideoCacheEnd:(NSInteger)utcTimeStamp channel:(int)channel;

// 播放缓存结束回调
- (void)cloudVideoEnd;

// 返回下载地址 (逐渐废弃)
- (void)cloudDeviceManagerDownloadFilePath:(NSString *)filePath;

// 下载成功
- (void)cloudDeviceManagerDownloadSuccessFilePath:(NSString *)filePath channel:(int)channel;

// 下载失败
- (void)cloudDeviceManagerDownloadFailChannel:(int)channel;

@end

NS_ASSUME_NONNULL_BEGIN

@interface MSDKCloudDeviceManager : NSObject

@property (nonatomic, weak) id<MSDKCloudDeviceManagerDelegate> delegate;

// 获取设备信息
- (void)getDeviceInfoByLicense:(NSString *)license success:(void(^)(void))success failure:(void(^)(id error))failure;

/// 查询设备某天的云事件，带时长返回
/// - Parameters:
///   - dateStr: 日期字符串 示例：2022-10-24
///   - successBlock: 成功返回
///   - failureBlock: 失败返回
- (void)getSomeDayCloudEventListWithDate:(NSString *)dateStr successBlock:(void(^)(NSMutableArray *eventArr))successBlock failureBlock:(void(^)(id error))failureBlock;

/// 查询单台设备N天的云事件
/// - Parameters:
///   - startDate: 开始日期字符串 示例：2022-10-24
///   - endDate: 结束日期字符串 示例：2022-10-24
///   - successBlock: 成功返回
///   - failureBlock: 失败返回
- (void)getDaysCloudEventListWithLicense:(NSString *)startDate endDate:(NSString *)endDate success:(void(^)(NSMutableArray *eventArr))success failure:(void(^)(id error))failure;

/// 下载
/// - Parameters:
///   - startHmsInterval: //开始时间距离当天00:00:00的秒数
///   - endHmsInterval: //结束时间距离当天00:00:00的秒数
///   - model: 云事件&云录像model
///   - errorCallBack:返回错误
- (void)startCloudDownloadWithTimeInterval:(NSInteger)startHmsInterval endTime:(NSInteger)endHmsInterval model:(MSDKCloudEventModel *)model errorCallBack:(void(^)(MSDKCloudManagerErrorType error))errorCallBack;

// 播放一个start->end的视频  开始播放
/// - Parameters:
///   - startHmsInterval: //开始时间距离当天00:00:00的秒数
///   - endHmsInterval: //结束时间距离当天00:00:00的秒数
///   - model: 云事件&云录像model
///   - errorCallBack:返回错误
///   - 注:云事件由于没有结束时间，一般建议云事件可控制在事件时间+20s作为结束时间来使用（一个云文件大小为5s左右，可按需控制结束时间长度）
- (void)startCloudPlayWithTimeInterval:(NSInteger)startHmsInterval endTime:(NSInteger)endHmsInterval model:(MSDKCloudEventModel *)model errorCallBack:(void(^)(MSDKCloudManagerErrorType error))errorCallBack;

//  注：次方法成对使用，即使用完pausePlay后，一定要调用continuePlay再继续其他操作。
/// 暂停播放  （注意此方法要和继续播放方法成对调用）
- (BOOL)pauseCloudPlay;

/// 继续播放 （注意此方法要和暂停播放方法成对调用）
- (BOOL)continueCloudPlay;

// 停止播放
/// 如果重新调用播放api，建议先停止。
- (BOOL)stopCloudPlay;

/// 禁音
- (BOOL)muteCloudAudio;

/// 取消禁音
- (BOOL)cancleCloudMute;

@end

NS_ASSUME_NONNULL_END
