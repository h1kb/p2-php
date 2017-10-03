<?php
/**
 * rep2 - 管理者用設定ファイル
 *
 * このファイルの設定は、必要に応じて変更してください
 */

// ----------------------------------------------------------------------
// {{{ データ保存ディレクトリ

// それぞれパーミッションは0777等、Webサーバーが書き込めるようにしておく。
// Webからアクセスできないところに配置するのが望ましい。

// p2で使用する基本のデータ保存ディレクトリ
//$_conf['data_dir'] = P2_BASE_DIR . '/data';
$_conf['data_dir'] = '/data';

// 取得スレッドの dat データ保存ディレクトリ
$_conf['dat_dir'] = $_conf['data_dir'] . '/dat';

// 取得スレッドの idx データ保存ディレクトリ
$_conf['idx_dir'] = $_conf['data_dir'] . '/idx';

// 初期設定データ保存ディレクトリ
$_conf['pref_dir'] = $_conf['data_dir'] . '/pref';

// SQLite3データベース保存ディレクトリ
$_conf['db_dir'] = $_conf['data_dir'] . '/db';

// }}}
// ----------------------------------------------------------------------
// {{{ リバースプロキシ

// リバースプロキシを通してアクセスする際のホスト名。
// $_SERVER['HTTP_HOST'] を上書きし、オリジナルの値を
// $_SERVER['X_REP2_ORIG_HTTP_HOST'] に書き込む。
// 'auto' の場合、$_SERVER['HTTP_X_FORWARDED_HOST'] が
// 設定されている場合だけ適用される
$_conf['reverse_proxy_host'] = '';  // ("")

// リバースプロキシを通してアクセスする際のポート番号。
// $_SERVER['HTTP_PORT'] を上書しき、オリジナルの値を
// $_SERVER['X_REP2_ORIG_HTTP_PORT'] に書き込む。
// 'auto' の場合、$_SERVER['HTTP_X_FORWARDED_PORT'] が
// 設定されている場合だけ適用される。
$_conf['reverse_proxy_port'] = '';  // ("")

// リバースプロキシを通してアクセスする際のパス。
// $_SERVER['REQUEST_URI'], $_SERVER['SCRIPT_NAME'], $_SERVER['PHP_SELF']
// の前に付加される。
// オリジナルの値は、それぞれ $_SERVER["X_REP2_ORIG_{$key}"] に書き込まれる。
// reverse_proxy_host が無効のときは無視される。
$_conf['reverse_proxy_path'] = '';  // ("")

// }}}
// ----------------------------------------------------------------------
// {{{ 書き込み

// 書き込みを掲示板サーバで直接行うように （する:1, しない:0）
$_conf['disable_res'] = 0;          // (0)

// 書き込んだレスの最大記録数 // この設定は現在は機能していない
//$_conf['posted_rec_num'] = 1000;    // (1000)

// }}}
// ----------------------------------------------------------------------
// {{{ 各種設定

// sessionデータの保存管理 (PHPデフォルト:'', p2でファイル管理:'p2')
$_conf['session_save'] = 'p2';      // ('p2')

// Cookie IDの有効期限日数
$_conf['cid_expire_day'] = 30;      // (30)

// ネットワーク接続タイムアウト時間 (秒)
// @deprecated use $_conf['http_conn_timeout'] and $_conf['http_read_timeout']
$_conf['fsockopen_time_limit'] = 7; // (7)

// HTTP接続タイムアウト時間 (秒)
$_conf['http_conn_timeout'] = 2; // (2)

// HTTP読込タイムアウト時間 (秒)
$_conf['http_read_timeout'] = 8; // (8)

// p2の最新バージョンを自動チェック(する:1, しない:0)
$_conf['updatan_haahaa'] = 1;       // (1)

// p2status（アップデートチェック）のキャッシュを更新せずに保持する時間 (日)
$_conf['p2status_dl_interval'] = 7; // (7)

// スレッドサブジェクト一覧のデフォルト表示数 (100, 150, 200, 250, 300, 400, 500, "all")
$_conf['display_threads_num'] = 150; // (150)

// 板 menu のキャッシュを更新せずに保持する時間 (hour)
$_conf['menu_dl_interval'] = 1;     // (1)

// subject.txt のキャッシュを更新せずに保持する時間 (秒)
$_conf['sb_dl_interval'] = 300;     // (300)

// dat のキャッシュを更新せずに保持する時間 (秒) // この設定は現在は機能していない
// $_conf['dat_dl_interval'] = 20;  // (20)

// ログインログを記録（する:1, しない:0）
$_conf['login_log_rec'] = 1;        // (1)

// ログインログの記録数
$_conf['login_log_rec_num'] = 200;  // (200)

// 前回ログイン情報を表示（する:1, しない:0）
$_conf['last_login_log_show'] = 1;  // (1)

// 新着まとめ読みのキャッシュを残す数 (無効:0, 無限:-1)
$_conf['matome_cache_max'] = 5; // (5)

// }}}
// ----------------------------------------------------------------------
// {{{ 携帯アクセスキー

$_conf['k_accesskey'] = array(
    'matome' => '3', // 新まとめ
    'latest' => '3', // 新
    'res'    => '7', // ﾚｽ
    'above'  => '2', // 上
    'up'     => '5', // （板）
    'prev'   => '4', // 前
    'bottom' => '8', // 下
    'next'   => '6', // 次
    'info'   => '9', // 情
    'dele'   => '*', // 削
    'filter' => '#', // 索
);

// }}}
// ----------------------------------------------------------------------
// {{{ 拡張パック

include P2_CONFIG_DIR . '/conf_admin_ex.inc.php';

// }}}

/*
 * Local Variables:
 * mode: php
 * coding: cp932
 * tab-width: 4
 * c-basic-offset: 4
 * indent-tabs-mode: nil
 * End:
 */
// vim: set syn=php fenc=cp932 ai et ts=4 sw=4 sts=4 fdm=marker:
