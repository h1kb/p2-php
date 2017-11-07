<?php
/**
 * rep2 - �E�X���b�h����JSON�`���ŕԂ�
 */

require_once __DIR__ . '/../init.php';
require_once P2_LIB_DIR . '/get_info.inc.php';

$_login->authorize(); // ���[�U�F��

$host = isset($_GET['host']) ? $_GET['host'] : null; // "pc.2ch.net"
$bbs  = isset($_GET['bbs'])  ? $_GET['bbs']  : null; // "php"
$key  = isset($_GET['key'])  ? $_GET['key']  : null; // "1022999539"

header('Content-Type: application/json; charset=UTF-8');
if (!$host || !$bbs) {
    echo 'null';
} elseif (!$key) {
    echo info_js_get_board_info($host, $bbs);
} else {
    echo info_js_get_thread_info($host, $bbs, $key);
}

// {{{ info_js_get_board_info()

/**
 * �����擾����
 *
 * @param   string  $host
 * @param   string  $bbs
 * @return  string  JSON�G���R�[�h���ꂽ���
 */
function info_js_get_board_info($host, $bbs)
{
    return info_js_json_encode(get_board_info($host, $bbs));
}

// }}}
// {{{ info_js_get_thread_info()

/**
 * �X���b�h�����擾����
 *
 * @param   string  $host
 * @param   string  $bbs
 * @param   string  $key
 * @return  string  JSON�G���R�[�h���ꂽ�X���b�h���
 */
function info_js_get_thread_info($host, $bbs, $key)
{
    return info_js_json_encode(get_thread_info($host, $bbs, $key));
}

// }}}
// {{{ info_js_json_encode()

/**
 * Shift_JIS�̒l��UTF-8�ɕϊ����Ă���JSON�G���R�[�h����
 *
 * @param   mixed   $values
 * @return  string  JSON
 */
function info_js_json_encode($values)
{
	// mb_convert_variables�͖{���������z��ł̓����ۏ؂��Ă��Ȃ��̂�
	// array_walk_recursive�ŉ񂷁B
	// array_walk_recursive���������z��Ή����ĂȂ��͂������ǂƂ肠���������B�B�B
	// https://bugs.php.net/bug.php?id=66964
    array_walk_recursive($values, function(&$value) {
        mb_convert_variables('UTF-8', 'CP932', $value);
    }); 
    return json_encode($values);
}

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
