<?php
/*
�g�p��:
$stalker = new Stalker();
$stalker->host = $host; // �w�肵�Ȃ��ꍇ��2ch�Ƃ݂Ȃ�
$stalker->bbs  = $bbs;
if ($stalker->isEnabled()) {
    // bbs, date, id�̎w�肪�K�v
    echo $stalker->getIDURL();
}
*/

class Stalker
{
    public $host;   // �̃z�X�g
    public $bbs;    // �̃f�B���N�g����
    public $id;     // ID
    protected $enabled;

    /**
     * ID�X�g�[�J�[�ɑΉ����Ă��邩���ׂ�
     * $board���Ȃ����load�����s�����
     */
    public function isEnabled()
    {
        if ($this->host) {
            if (!P2HostMgr::isHost2chs($this->host)) {
                return false;
            }
        }
        return preg_match('/plus$/', $this->bbs);
    }

    /**
     * ID��URL���擾����
     */
    public function getIDURL()
    {
        return "http://stick.newsplus.jp/id.cgi?bbs={$this->bbs}&word=" . rawurlencode($this->id);
    }
}
