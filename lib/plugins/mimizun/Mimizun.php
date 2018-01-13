<?php
/*
�g�p��:
$mimizun = new Mimizun();
$mimizun->host = $host; // �w�肪�Ȃ��ꍇ��2ch�Ƃ݂Ȃ�
$mimizun->bbs  = $bbs;
$mimizun->from  = 0;    // 1:���C�u, 2:�ߋ�, ����ȊO:�S��
if ($mimizun->isEnabled()) {
    $mimizun->id = $id;
    echo $mimizun->getIDURL();
}

loadBoard�֌W�͈�x�����s����Ȃ����isEnable�ł��Ăяo�����̂ŁA���Ɏ��s����K�v�͂Ȃ��B
�Ď擾�������ꍇ�Ɏg�����ƁB
loadAll�c�S�Ă̔��X�g��ǂݍ���
loadLive�c���C�u�X���b�h�̔��X�g��ǂݍ���
loadKako�c�ߋ����O�̔��X�g��ǂݍ���
isEnable�c����host, bbs��from�őΉ����Ă��邩�`�F�b�N
getIDURL�c����ID�݂݂̂���ID������URL��Ԃ�
*/
class Mimizun
{
    public $liveBoards; //���C�u�X���b�h�̑Ή���
    public $kakoBoards; //�ߋ����O�̑Ή���
    public $host;       // �z�X�g(�Ȃ�ׂ��w�肷�邱��)
    public $bbs;        // �̃f�B���N�g���� (�K���w�肷�邱��)
    public $from = 0;   // 0:�S��, 1:���C�u, 2:�ߋ�
    public $id;         // ID (ID�����ŕK�v)
    protected $enabled;

    /**
     * �݂݂���Ή���ǂݍ���
     */
    public function load($type)
    {
        global $_conf;

        // �Ή��̎擾
        switch($type) {
            case 0:
                $url = 'http://mimizun.com/search/2chlive.html';
                $path = $_conf['cache_dir'] . '/search.mimizun.com/2chlive.html';
                $match = '{<input type="checkbox" name="idxname" value="_(.+?)">}';
                break;
            case 1:
                $url = 'http://mimizun.com/search/2ch.html';
                $path = $_conf['cache_dir'] . '/search.mimizun.com/2ch.html';
                $match = '{<input type="checkbox" name="idxname" value="(.+?)">}';
                break;
        }
        // �L���b�V���p�f�B���N�g����������΍쐬
        FileCtl::mkdir_for($path);
        // ���j���[�̃L���b�V�����Ԃ�10�{�L���b�V��
        P2Commun::fileDownload($url, $path, $_conf['menu_dl_interval'] * 36000);
        $file = @file_get_contents($path);
        preg_match_all($match, $file, $boards);
        return $boards[1];
    }

    /**
     * �݂݂���Ή���(���C�u)��ǂݍ���
     */
    public function loadLive()
    {
        $this->liveBoards = $this->load(0);
    }

    /**
     * �݂݂���Ή���(�ߋ����O)��ǂݍ���
     */
    public function loadKako()
    {
        $this->kakoBoards = $this->load(1);
    }

    /**
     * �݂݂���Ή���ǂݍ���
     */
    public function loadAll()
    {
        $this->loadLive();
        $this->loadKako();
    }

    /**
     * �݂݂��񌟍��ɑΉ����Ă��邩���ׂ�
     */
    public function isEnabled()
    {
        // host���Z�b�g����ĂȂ���������Ȃ��̂�
        // (�Z�b�g����Ă��Ȃ����2ch�Ƃ݂Ȃ�)
        if ($this->host) {
            // �܂�BBS�Ȃ�false
            if (P2HostMgr::isHostMachiBbs($this->host)) {
                return false;
            }
            // 2ch�łȂ����false
            if (!P2HostMgr::isHost2chs($this->host)) {
                return false;
            }
        }
        $this->enabled = true;
        return $this->enabled;
    }

    /**
     * �݂݂���ID������URL��Ԃ�
     */
    public function getIDURL()
    {
        return "http://mimizun.com/search/perl/idsearch.pl?board={$this->bbs}&id={$this->id}";
    }

}
