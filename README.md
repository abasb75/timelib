۱. ابتدا داکر را نصب میکنیم
۲. دستور بیلد را وراد میکنیم:

sudo docker build \
  --build-arg USER_UID=$(id -u) --build-arg USER_GID=$(id -g) --build-arg USERNAME=$(whoami) \
  -t timelib .

۳. دستور ورود به ترمینال داکر را وارد میکنیم:
sudo docker run -it --rm \
  --user $(id -u):$(id -g) \
  -v "$(pwd)":/timelib -w /timelib \
  timelib bash -login


۴. ادامه را از فایل راهنمای این مسیر ادامه میدهیم:
cd /timelib/zones

