//
//  MSDKCloudEventModel.h
//  MSDKIOT
//
//  Created by lsqMacbook Pro        on 2025/3/12.
//

#import <Foundation/Foundation.h>

typedef NS_ENUM(NSInteger, MSDKDeviceRecordType) {
    MSDKDeviceRecordType_NoRecord,
    MSDKDeviceRecordType_CloudRecord,
    MSDKDeviceRecordType_SDCardRecord
};

typedef NS_ENUM(NSInteger, MSDKCloudManagerErrorType) {
    MSDKCloudManagerErrorType_Ok,
    MSDKCloudManagerErrorType_NoFile,
    MSDKCloudManagerErrorType_NetworkError
};

NS_ASSUME_NONNULL_BEGIN

@interface MSDKCloudEventModel : NSObject

@property (nonatomic, assign) MSDKDeviceRecordType type;

#pragma mark - cloudVideo
@property (nonatomic, copy) NSString *startTime;                //2019-01-16 16:18:07 (云录像开始时间)
@property (nonatomic, copy) NSString *endTime;                  //2019-01-16 19:24:47 (云录像结束时间)

#pragma mark - cloudVideo&CloudEvet
@property (nonatomic, copy) NSString *ossId;                    //云资源id(云录像和云事件均拥有的参数)

#pragma mark - cloudEvent
@property (nonatomic, copy) NSString *timeZone;                 //时区 "GMT+8,Asia/Shanghai"
@property (nonatomic, copy) NSString *id;                       //云事件id
@property (nonatomic, copy) NSString *deviceId;                 //设备id
@property (nonatomic, assign) BOOL playEnable;                  //仅对事件，是否可播放
@property (nonatomic, copy) NSString *cloudTime;                //2019-01-16 19:24:47 (云事件时间)
@property (nonatomic, copy) NSString *imagePath;                //图片地址
@property (nonatomic, copy) NSString *iconPath;                 //事件图片
@property (nonatomic, copy) NSString *recordingMode;            //记录模式
@property (nonatomic, copy) NSString *tag;
@property (nonatomic, copy) NSString *tagName;
@property (nonatomic, copy) NSString *tagMessage;
@property (nonatomic, copy) NSDictionary *tagExtra;             //额外数据

#pragma mark - 解析数据

@property (nonatomic, assign) NSInteger startHmsInterval;       //开始时间距离当天00:00:00的秒数
@property (nonatomic, assign) NSInteger endHmsInterval;         //结束时间距离当天00:00:00的秒数
@property (nonatomic, assign) NSInteger recordDuration;         //时长 单位s
@property (nonatomic, copy) NSString *hourMinusSecStr;          //16:18:10
@property (nonatomic, copy) NSString *durationMinusSecStr;

@property (nonatomic, assign) NSInteger startTs;                 // 起始时间戳
@property (nonatomic, assign) NSInteger endTs;                   // 结束时间戳


@end

NS_ASSUME_NONNULL_END
