1. 設定方法

　auditd サービスが起動していることを確認し、次のコマンドを実行してくだ さい。
　
　----------------------------------------------
　# auditctl -a exit,always -F arch=b64 -S kill -S tkill -S rt_sigqueueinfo -F a1=9 -k
 signal_sent
　# auditctl -a exit,always -F arch=b64 -S tgkill -S rt_tgsigqueueinfo -F a2=9 -k sign
al_sent
　---------------------------------------------
　
　このルール追加により、64 ビットプログラムを対象とした、シグナル送信系 のシス
　テムコール(kill、tkill、rt_sigqueueinfo、tgkill、rt_tgsigqueueinfo) を 監視し
　ます。その際、シグナル番号 9 (SIGKILL) に限定しています。
　
　※ auditctl コマンドの詳細は、オンラインマニュアルをご確認ください。
　
2. 事象の再現を待つ

　設定が完了すると、ログが /var/log/audit/audit.log に記録されていきま す。な
　お、プログラムの動作状況によりログの量は変動しますので、調査対象のサー バで設
　定した後に、ログの量が多くなりすぎていないかどうかを確認してください。 また、
　ログファイルは /etc/audit/auditd.conf の設定に従って自動的にローテー ションさ
　れていくため、ローテーションにより削除されてしまう前に確認する必要があ りま
　す。

3. SIGKILL の送信元をログから確認する

　事象が発生したら、 ausearch コマンドを用いて /var/log/audit/audit.log の内容
　を検索します。事象が発生した時刻の直前に、プロセスを終了させるシグナル を送信
　しているログが見つかれば、SIGKILL を送信しているプロセスを特定すること ができ
　ます。
　
　---------------------------------------------
　# ausearch -k signal_sent
　---------------------------------------------
　
　---------- 実行結果例 -----------------------
　time->Wed Dec 10 14:17:07 2014
　type=OBJ_PID msg=audit(1418188627.862:14281): opid=14619 oauid=0 ouid=0 oses=1　 oco
mm="signal_test"
　type=SYSCALL msg=audit(1418188627.862:14281): arch=c000003e syscall=62 success　=yes
 exit=0 a0=391b a1=12 a2=3cc918fee8 a3=7fffef79b680 items=0
　ppid=1953 pid=14618 auid=0 uid=0 gid=0 euid=0 suid=0 fsuid=0 egid=0 sgid=0 fsg　id=0
 tty=pts0 ses=1 comm="signal_test" exe="/tmp/signal_test"
　key="signal_sent"
　---------------------------------------------
　
　syscall= で指定されている数値 (10進数)がシステムコール番号で、 arch= の値と
　組み合わせることによりどのシステムコールが発行されたのかを判断します。
　
　comm= で指定されている文字列がシグナル送信側のプロセス名、 exe= で指定 されて
　いるパス名がシグナル送信側プロセスの実行ファイルを示しています。ocomm= で指定
　されている文字列が、シグナル受信側のプロセス名です。

4. 設定を元に戻す

　設定した audit の記録ルールを削除するには次のコマンドを実行してください。
　
　---------------------------------------------
　# auditctl -D -k signal_sent
　---------------------------------------------