ابتدا tzdata را از اینجا دانلود میکنیم 
https://www.iana.org/time-zones

دوفایل که با tzdata و tzcode شروع میشود
این دوفایل را به پوشه timelib/zones کپی کرده و اکسترکت میکنیم

1. ابتدا تایمزون رو در پوشه tzdata2025 ویرایش کنید

2. سپس از دو زیرا را تبدیل به tar.gz کنید:

```sh
tar -czvf tzcode2025b.tar.gz -C ./tzcode2025b .
tar -czvf tzdata2025b.tar.gz -C ./tzdata2025b .
```

۳. سپس دستور make را اجرا کنید:
```sh
make
```

۴. فایل timelib/zones/timezonedb.h تولید شده است.