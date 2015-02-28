#import "support.h"

int main() {

  mud_object_t * date_obj = initMudObjectWithNSObject([NSDate date]);
  mud_date_t * date = date_obj->ptr;

  NSLog(@"Date should be: %@ == %@", [NSDate date], nsWithMudObject(date_obj));

  NSLog(@"%@", nsDateWithMudDate(mud_date_alloc_from_string("2014-12-31T17:31:22Z")));
  NSLog(@"mud_date: %ld - %ld - %ld %ld : %ld", date->year, date->mon, date->mday, date->hour, date->sec);
  
  NSLog(@"%@", nsDateWithMudDate(mud_date_alloc_from_string("2014-12-31T17:31:22+08:00")));
  NSLog(@"mud_date: %ld - %ld - %ld %ld : %ld", date->year, date->mon, date->mday, date->hour, date->sec);
  
  mud_date_adjust(date, 7200);
  NSLog(@"mud_date: %ld - %ld - %ld %ld : %ld", date->year, date->mon, date->mday, date->hour, date->sec);
  NSLog(@"Date should be: 2 hour + %@ == %@", [NSDate date], nsWithMudObject(date_obj));

  mud_date_adjust(date, -7200);
  mud_date_adjust(date, 3600 * 48);
  NSLog(@"mud_date: %ld - %ld - %ld %ld : %ld", date->year, date->mon, date->mday, date->hour, date->sec);
  NSLog(@"Date should be: 2 days + %@ == %@", [NSDate date], nsWithMudObject(date_obj));
  
  mud_date_adjust(date, -3600 * 48);
  mud_date_adjust(date, 3600 * 24 * 30);
  NSLog(@"mud_date: %ld - %ld - %ld %ld : %ld", date->year, date->mon, date->mday, date->hour, date->sec);
  NSLog(@"Date should be: 30 days + %@ == %@", [NSDate date], nsWithMudObject(date_obj));

  mud_date_adjust(date, -3600 * 24 * 30);
  mud_date_adjust(date, 3600 * 24 * 365);
  NSLog(@"mud_date: %ld - %ld - %ld %ld : %ld", date->year, date->mon, date->mday, date->hour, date->sec);
  NSLog(@"Date should be: 365 days + %@ == %@", [NSDate date], nsWithMudObject(date_obj));

  mud_date_adjust(date, 3600 * 24 * 365);
  NSLog(@"mud_date: %ld - %ld - %ld %ld : %ld", date->year, date->mon, date->mday, date->hour, date->sec);
  NSLog(@"Date should be: 365 days * 2 + %@ == %@", [NSDate date], nsWithMudObject(date_obj));

}