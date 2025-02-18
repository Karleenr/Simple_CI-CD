## Part 1. Setting up the gitlab-runner

Установил образ Ubuntu 22.04 LTS

![Alt text](src/screenshots/p1.1.1.png)

Поднял образ и установил там ssh и openssh-server

Подключился к серверу на VM через SSH 

![Alt text](src/screenshots/p1.1.png)

Скачал и установил на виртуальную машину gitlab-runner.

Запустил gitlab-runner и зарегистрируй его для использования в текущем проекте (DO6_CICD).

![Alt text](src/screenshots/p1.2.png)

Инструкция по установке: https://docs.gitlab.com/runner/install/linux-manually.html

## Part 2. Building

Написал этап для CI по сборке приложений из проекта C2_SimpleBashUtils.

В файле gitlab-ci.yml добавил этап запуска (build) сборки через мейк файл из проекта C2 по пути /src/cat/   src/grep/.

Файлы, полученные после сборки (артефакты), сохранил в директорию их компиляциисо сроком хранения 30 дней.


![Alt text](src/screenshots/p2.1.png)


default:
  tags: [karleenr]


Секция default в файле .gitlab-ci.yml используется для определения глобальных настроек, которые будут применены ко всем заданиям (билдам) в пайплайне. Это позволяет избежать дублирования кода и упрощает поддержку конфигурации. В теге просто указал свой ник.


stages:
  - build
  - clang
  - test
  - deploy

Прописал стейджи (этапы), которые будут в проекте.  

Далее расписал build_stage, в котором указал сам стейдж, прописал скрипт, который заходит в директории cat и grep и компилирует проект в исполняемые файлы (артефакты) s21_cat и s21_grep. В artefacts указал местоположение артефактов и их срок хранения ```expire_in: ```

after_script: - bash src/bot_telegram.sh 

Поле, которое после выполнения скрипта выполняет скрипт для Part6, который уведомляет о исходе билда в телеграме. Такая стрчока есть в каждом стейдже.

![Alt text](src/screenshots/p2.2.png)

![Alt text](src/screenshots/p2.3.png)

## Part 3. Codestyle test

Написал этап для CI, который запускает скрипт кодстайла (clang-format).

Если кодстайл не прошел, то «зафейлил» пайплайн.

В пайплайне отобразил вывод утилиты clang-format.

![Alt text](src/screenshots/p3.1.png)

По аналогии с Part2 сделал стейдж clang, который проверяет проект на clang-format. 

Проверил на фейл

![Alt text](src/screenshots/p3.2.png)

![Alt text](src/screenshots/p3.3.png)

![Alt text](src/screenshots/p3.4.png)

![Alt text](src/screenshots/p3.5.png)

## Part 4. Integration tests

Написал этап для CI, который запустит интеграционные тесты.

Для проекта C2_SimpleBashUtils взял свои уже написанные интеграционные тесты.

Если тесты не прошли, то «зафейлил» пайплайн.

В пайплайне отобразил вывод, что интеграционные тесты успешно прошли / провалились.

![Alt text](src/screenshots/p4.5.png)

![Alt text](src/screenshots/p4.1.png)

![Alt text](src/screenshots/p4.2.png)

![Alt text](src/screenshots/p4.3.png)

![Alt text](src/screenshots/p4.4.png)

Тоже самое, что и в Part2-Part3

## Part 5. Deployment stage

Поднял вторую виртуальную машину Ubuntu Server 22.04 LTS.

![Alt text](src/screenshots/p5.1.png)

Написал этап для CD, который «разворачивает» проект на другой виртуальной машине.

![Alt text](src/screenshots/p5.2.png)

В файле gitlab-ci.yml добавил этап запуска написанного скрипта.

В этом примере по развертыванию в продакшн требуется ручное подтверждения (when: manual) и может завершиться с ошибкой без влияния на общий статус пайплайна (allow_failure: true).


Для этого аписал bash-скрипт, который при помощи ssh и scp копирует файлы, полученные после сборки (артефакты), в директорию /usr/local/bin второй виртуальной машины.

![Alt text](src/screenshots/p5.3.png)

Запустил этот этап вручную при условии, что все предыдущие этапы прошли успешно.

![Alt text](src/screenshots/p5.4.png)

В случае ошибки «зафейлил» пайплайн.

![Alt text](src/screenshots/p5.5.png)

![Alt text](src/screenshots/p5.6.png)

Для того, чтобы подружить машины между собой, сделал им статический маршрут друг на друга 

![Alt text](src/screenshots/p5.7.png)

![Alt text](src/screenshots/p5.8.png)

Теперь необходимо соединить машины ssh-ключом, для этого использую команду ```ssh-keygen -t rsa``` для генерации ключа и ```ssh-copy-id karleenr2@172.24.116.8```

![Alt text](src/screenshots/p5.9.png)

Запушил изменения и посмотрел пайплайн

![Alt text](src/screenshots/p5.10.png)

![Alt text](src/screenshots/p5.11.png)

## Part 6. Bonus. Notifications

Настрил уведомления об успешном/неуспешном выполнении пайплайна через бота в Telegram.

С помощью документации в materials/notification.md создал бота в Telegram через @BotFather. Это дало мне API токен, который понадобится для аутентификации бота.

Создал скрипт bot_telegram.sh для вызова API Telegram и отправки сообщений.
Включил этот скрипт в файл .gitlab-ci.yml, чтобы он выполнялся после каждых стейджей.

![Alt text](src/screenshots/p6.1.png)

Сперва определил переменные (мой ID телеграма и токен созданного бота). 

Далее формируется URL для API телеги, и следом формируется текст.

И curl для отправки сообщений.

Флаг -s означает "silent" или "тихий режим". Он отключает вывод прогресса запроса в консоль, что может быть полезно при выполнении команды в скриптах или когда вы не хотите видеть дополнительную информацию.

Флаг -d используется для отправки данных на сервер. Обычно это используется для POST-запросов, когда вам нужно передать данные в теле запроса. 

В итоге, во время выполнения стейждей, в телеграм приходят уведомления о том, с каким результатом прошел стейдж

![Alt text](src/screenshots/p6.2.png)