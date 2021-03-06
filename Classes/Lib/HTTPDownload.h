#import <Foundation/Foundation.h>


@interface HTTPDownload : NSObject {
  NSURLConnection *connection;
  NSMutableURLRequest *request;
  NSHTTPURLResponse *response;
  NSMutableData *downloadData;
  void (^block)(id response);
  NSError *error;
  BOOL reportConnectionStatus;
}

@property (nonatomic, retain) NSURLConnection *connection;
@property (nonatomic, retain) NSMutableURLRequest *request;
@property (nonatomic, retain) NSHTTPURLResponse *response;
@property (nonatomic, retain) NSMutableData *downloadData;
@property (nonatomic, retain) NSError *error;
@property (nonatomic, assign) BOOL reportConnectionStatus;

+ (id)globalDelegate;
+ (void)setGlobalDelegate:(id)delegate;

+ (id)downloadFromURL:(NSURL *)theURL block:(void (^)(id response))theBlock;
+ (id)downloadFromURL:(NSURL *)theURL username:(NSString *)username password:(NSString *)password block:(void (^)(id response))theBlock;
+ (id)postToURL:(NSURL *)theURL body:(NSString *)body block:(void (^)(id response))theBlock;
+ (id)postToURL:(NSURL *)theURL body:(NSString *)body username:(NSString *)username password:(NSString *)password block:(void (^)(id response))theBlock;

+ (void)cancelDownloadsInProgress;

- (id)initWithURL:(NSURL *)theURL postBody:(NSString *)body username:(NSString *)username password:(NSString *)password block:(void (^)(id response))theBlock;

- (void)start;
- (void)cancel;

- (BOOL)errorOcurred;
- (NSString *)errorMessage;

- (void)yieldDownloadedData;

@end


@interface JSONDownload : HTTPDownload
@end


@interface ImageDownload : HTTPDownload {
  CGSize resizeTo;
}

@property (nonatomic, assign) CGSize resizeTo;

+ (id)downloadFromURL:(NSURL *)theURL resizeTo:(CGSize)resizeToSize block:(void (^)(id response))theBlock;
- (id)initWithURL:(NSURL *)theURL resizeTo:(CGSize)resizeTo block:(void (^)(id response))theBlock;

@end
