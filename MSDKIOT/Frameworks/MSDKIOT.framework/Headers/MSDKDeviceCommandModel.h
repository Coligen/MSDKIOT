//
//  MSDKDeviceCommandModel.h
//  MSDKIOT
//
//  Created by lsqMacbook Pro        on 2025/2/22.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN


@interface MSDKDeviceFileModel : NSObject

@property(nonatomic, copy) NSString *name;

@property(nonatomic, copy) NSString *path;

@property(nonatomic, copy) NSString *size;

@property(nonatomic, copy) NSNumber *timestamp;

@property(nonatomic, assign) int duration;

@end

NS_ASSUME_NONNULL_END
