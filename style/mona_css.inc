<?php
/**
 * rep2 - �X�^�C���ݒ�
 * for �A�N�e�B�u���i�[
 */

echo <<<EOSTYLE

/* �X�C�b�` */
span.aMonaSW {
	cursor: pointer;
}

/* �A�N�e�B�u���i�[:����AA�X�^�C���K�p */
.AutoMona {
	font-family: "{$_exconf['aMona']['aafont']}";
	font-size: {$_exconf['aMona']['auto_fontsize']};
	line-height: 100%;
	white-space: nowrap;
}

/* �A�N�e�B�u���i�[:AA�X�^�C���K�p */
.ActiveMona {
	font-family: "{$_exconf['aMona']['aafont']}";
	line-height: 100%;
	white-space: nowrap;
}

/* �A�N�e�B�u���i�[:���� */
.NoMona {
	font-family: "{$STYLE['fontfamily']}";
	font-size: {$STYLE['read_fontsize']};
	line-height: 130%;
	white-space: normal;
}

/* �A�N�e�B�u���i�[:����(���X�|�b�v�A�b�v) */
.NoMonaQ {
	font-family: "{$STYLE['fontfamily']}";
	font-size: {$STYLE['respop_fontsize']};
	line-height: 120%;
	white-space: normal;
}

EOSTYLE;

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