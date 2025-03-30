۱. ابتدا داکر را نصب میکنیم
۲. دستور بیلد را وراد میکنیم:
```sh
sudo docker build \
  --build-arg USER_UID=$(id -u) --build-arg USER_GID=$(id -g) --build-arg USERNAME=$(whoami) \
  -t timelib .
```

۳. دستور ورود به ترمینال داکر را وارد میکنیم:
```sh
sudo docker run -it --rm \
  --user $(id -u):$(id -g) \
  -v "$(pwd)":/timelib -w /timelib \
  timelib bash -login

```

۴. ادامه را از فایل راهنمای این مسیر ادامه میدهیم:
```sh
cd /timelib/zones
```

