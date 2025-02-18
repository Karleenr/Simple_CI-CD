#!/bin/bash

TELEGRAM_BOT_TOKEN="7559126221:AAHTpHq1zJfcBKbpK-GVvomVMkrmwhyMWc0"
TELEGRAM_USER_ID="my_telegram_id"

URL="https://api.telegram.org/bot$TELEGRAM_BOT_TOKEN/sendMessage"
TEXT="Project:+$CI_PROJECT_NAME%0A%0AJob name: $CI_JOB_NAME%0A%0AStatus:+$CI_JOB_STATUS"

curl -s -d "chat_id=$TELEGRAM_USER_ID&disable_web_page_preview=1&text=$TEXT" $URL > /dev/null