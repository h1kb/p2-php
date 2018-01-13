<?php
/*
rep2+wiki
samba�^�C�}�[���R���g���[������N���X�B
���C��:
getSamba($host, $bbs)       �c�莞��(�b)���擾(post_options_loader.inc.php�Ŏg��)
setWriteTime($host, $bbs)   �������񂾎���(=���ݎ���)���Z�b�g(post.php�Ŏg��
save()                      samba���X�g��ۑ�(setSamba�̌�Ɏ��s)
createTimer($time)          $time�b��samba�^�C�}�[�𐶐����ĕԂ�
���̑�(�ʏ햾���I�Ɏ��s����K�v�͂Ȃ�����:
load()                      samba���X�g��ǂݍ���(�����I�Ɏ��s�����)
getSambaTime($host, $bbs)   ��samba���擾
*/

class Samba
{
    protected $data = array();
    /* �f�[�^�\��
    bbs=bbs��
    $data[bbs][bbs]    bbs��(save�ŗ��p)
    $data[bbs][samba]  samba�̎���(�b)
    $data[bbs][write]  �������񂾎���(timer�֐�)
    $data[bbs][get]    samba���擾��������(timer)
    */
    protected $filename = 'p2_samba.txt';
    protected $isLoaded = false;

    public function load()
    {
        global $_conf;

        $lines = array();
        $path = $_conf['pref_dir'].'/'.$this->filename;
        if ($lines = @file($path)) {
            foreach ($lines as $l) {
                $lar = explode("\t", trim($l));
                if (strlen($lar[0]) == 0 || ($lar[1] === 0 && $lar[2] === 0)) {
                    continue;
                }
                $ar = array(
                    'bbs'   => $lar[0],  // bbs
                    'samba' => $lar[1],  // samba�̎���
                    'write'  => $lar[2], // �������񂾎���
                    'get'   => $lar[3],  // �擾����
                );

                $array[$lar[0]] = $ar;
            }

        }
        $this->data = $array;
        $this->isLoaded = true;
        return $array;
    }

    public function save()
    {
        global $_conf;

        $file = '';
        foreach ($this->data as $l) {
            $file .= "{$l['bbs']}\t{$l['samba']}\t{$l['write']}\t{$l['get']}\n";
        }
        $path = $_conf['pref_dir'].'/'.$this->filename;
        $fh = fopen($path, "w");
        fwrite($fh, $file);
        fclose($fh);
    }

    public function getSambaTime($host, $bbs)
    {
        if (!P2HostMgr::isHost2chs($host)) {
            return false;
        }
        // samba���擾
        $url = "http://{$host}/{$bbs}/index.html";
        $src = P2Commun::getWebPage($url, $errmsg);
        $match = '{<a href="http://www.2ch.net/">�Q�����˂�</a> BBS\.CGI - .*?\+Samba24=(\d+)}';
        preg_match($match, $src, $samba);
        if(!$this->isLoaded) $this->load();
        $this->data[$bbs]['bbs']   = $bbs;
        $this->data[$bbs]['get']   = time();
        $this->data[$bbs]['samba'] = $samba[1];

        return $samba[1];
    }

    /**
     * �������񂾎������Z�b�g
     */
    public function setWriteTime($host, $bbs)
    {
        global $_conf;

        if (!$this->isLoaded) {
            $this->load();
        }
        $this->data[$bbs]['write'] = time();
        // �ŏI�擾����samba_cache���Ԍo�߂����ꍇ
        if ((time() - $this->data[$bbs]['get']) > $_conf['samba_cache'] * 3600) {
            $this->getSambaTime($host, $bbs);
        }
    }

    // �c�莞�Ԃ��擾
    public function getSamba($host, $bbs)
    {
        if (!P2HostMgr::isHost2chs($host)) {
            return -1;
        }

        // �ǂݍ���ł��Ȃ���Γǂݍ���
        if (!$this->isLoaded) {
            $this->load();
        }
        // ��������ł��Ȃ���Ύc��0�b
        if ($this->data[$bbs]['write'] <= 0) {
            return 0;
        }
        // �K��0�b�Ȃ�v�Z����܂ł��Ȃ��c��0�b
        if ($this->data[$bbs]['samba'] <= 0) {
            return 0;
        }
        // �c�莞��
        $time = $this->data[$bbs]['write'] + $this->data[$bbs]['samba'] - time();
        return max(0, $time);
    }

    /*
    $time�b��samba�^�C�}�[�𐶐�
    */
    public function createTimer($time)
    {
        global $_conf;

        // getSamba�̃G���[�Ȃ̂Ő����ł��Ȃ�
        if ($time < 0) {
            return;
        }
        // �������߂�
        if ($time == 0) {
            return '�������߂邩��';
        }

        // PC
        return <<<EOP
        <span id="sambaSecond">����{$time}�b</span>
        <script type="text/JavaScript">
        <!--
        var intSecond = {$time};
        var timSamba = setInterval("sambaTimer()",1000);
        function sambaTimer() {
            intSecond -= 1;
            if (intSecond <= 0){
                clearInterval(timSamba);
                sambaSecond.innerHTML = "�������߂邩��";
            } else {
                sambaSecond.innerHTML = "����" + intSecond + "�b";
            }
        }
        // -->
        </script>
EOP;
    }
}
