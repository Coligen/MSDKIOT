//
//  MSDKIOT.h
//  MSDKIOT
//
//  Created by lsqMacbook Pro        on 2025/2/10.
//

#import <Foundation/Foundation.h>


typedef NS_ENUM(NSInteger, MSDKIOTNETWORK) {
    MSDKIOTNETWORK_TEST,            // 测试环境
    MSDKIOTNETWORK_PRODUCT          // 生产环境
};


typedef NS_ENUM(NSInteger, MSDKDATASTATUS) {
    MSDK_DATA_STATUS_OK,            // 流量正常
    MSDK_DATA_STATUS_EXHAUSTED,     // 流量不足
    MSDK_DATA_STATUS_EXPIRED        // 套餐到期
};


@interface MSDKIOT : NSObject

+ (MSDKIOT *)shareInstance;

// 设置环境
- (void)setNetwork:(MSDKIOTNETWORK)network;

/// 登录接口
/// @param userId 账号
/// @param success 成功
/// @param failure 失败
- (void)login:(NSString *)userId success:(nullable void (^)(NSString *token))success failure:(nullable void (^)(NSError *error))failure;

/// 初始化IOT平台
/// @param token   tk码
- (void)initIOTWithToken:(NSString *)token callback:(void (^)(BOOL isSucceed, NSString *msg, NSInteger code))block;

/// 绑定设备接口
/// @param serialInfo   序列号
/// @param deviceName   设备名
/// @param vin   vin码
/// @param token   tk码
/// @param block   结果
- (void)bindDevice:(NSString *)serialInfo deviceName:(NSString *)deviceName vin:(NSString *)vin token:(NSString *)token callback:(void (^)(BOOL isSucceed, NSString *deviceId, NSString *msg, NSInteger code))block;

/// 解绑设备
/// @param serialInfo   序列号
/// @param token   tk码
/// @param block   结果
- (void)unBindDevice:(NSString *)serialInfo token:(NSString *)token callback:(void (^)(BOOL isSucceed, NSString *msg, NSInteger code))block;

/// 获取设备列表
/// @param pageSize 页大小
/// @param pageNum 页码
/// @param token tk码
/// @param success 成功 status：设备在线状态（0：离线，1:在线）
/// @param failure 失败
- (void)getDevicesList:(int)pageSize pageNum:(int)pageNum token:(NSString *)token success:(void(^)(NSMutableArray *result))success failure:(void(^)(id error))failure;

/// 获取设备详细信息
/// @param deviceId 设备ID
/// @param token tk码
/// @param success 成功   status：设备在线状态（0：离线，1:在线）
/// @param failure 失败
- (void)getDeviceInfo:(NSString *)deviceId token:(NSString *)token success:(void(^)(NSMutableDictionary *result))success failure:(void(^)(id error))failure;

/// 获取设备卡流量
/// @param iccid : 设备上网卡id
/// @param token : 登录token
/// @param success : 成功回调，返回剩余流量(remaining, 单位KB)、总流量(total, 单位KB)、套餐信息(packageType)及流量到期时间(expire).
/// @param failure ：失败回调
- (void)getcCardDataRemaining:(NSString *)iccid token:(NSString *)token success:(void(^)(NSInteger remain, NSInteger total,NSInteger packageType,NSInteger expire))success failure:(void(^)(id error))failure;

/// 获取流量充值接口
/// @param serialInfo   序列号
/// @param token : 登录token
/// @param success : 成功回调，返回流量充值链接
/// @param failure ：失败回调

- (void)getDataRechargeWithSerialInfo:(NSString *)serialInfo token:(NSString *)token success:(void(^)(NSString *dataRechargeh5Url))success failure:(void(^)(id error))failure;

/// 调用流量充值
/// @param dataRechargeh5Url   流量充值链接
- (void)openDataRecharge:(NSString *)dataRechargeh5Url;


@end
