/*
 * rep2expack - �X���ꗗ�pJavaScript
 */

// {{{ rep2.subject.setWindowTitle()

rep2.subject.setWindowTitle = function () {
	if (rep2.subject.properties.shinchaku_ari) {
		window.top.document.title = '��' + rep2.subject.properties.page_title;
	} else {
		if (window.top != window.self) {
			window.top.document.title = window.self.document.title;
		}
	}
};

// }}}
// {{{ rep2.subject.changeNewAllColor()

rep2.subject.changeNewAllColor = function () {
	$('#smynum1, #smynum2, a.un_a').css('color', rep2.subject.properties.ttcolor);
};

// }}}
// {{{ rep2.subject.jumpMatomeLimit()

rep2.subject.jumpMatomeLimit = function (matome_url) {
	var unum_limit = window.prompt('�V�����w�肵�������ȉ��̃X�������܂Ƃߓǂ݂��܂��B','100');
	if (unum_limit) {
		matome_url +='&unum_limit='+unum_limit;
		if (top == self) {
			window.location = matome_url;
		} else {
			parent.read.location.href = matome_url;
		}
	}
};

// }}}
// {{{ rep2.subject.changeUnReadColor()

rep2.subject.changeUnReadColor = function (idnum) {
	$('#un' + idnum).css('color', rep2.subject.properties.ttcolor);
}

// }}}
// {{{ rep2.subject.changeThreadTitleColor()

rep2.subject.changeThreadTitleColor = function (idnum) {
	$('#tt' + idnum + ', #to' + idnum).css('color', rep2.subject.properties.ttcolor_v);
};

// }}}
// {{{ rep2.subject.deleteLog()

rep2.subject.deleteLog = function (query, from) {
	var width = rep2.subject.properties.pop_size[0];
	var height = rep2.subject.properties.pop_size[1];
	return deleLog(query, width, height, 'subject', from);
};

// }}}
// {{{ rep2.subject.setFavorite()

rep2.subject.setFavorite = function (query, favdo, from) {
	var width = rep2.subject.properties.pop_size[0];
	var height = rep2.subject.properties.pop_size[1];
	return setFavJs(query, favdo, width, height, 'subject', from);
};

// }}}
// {{{ rep2.subject.openSubWindow()

rep2.subject.openSubWindow = function (url) {
	var width = rep2.subject.properties.pop_size[0];
	var height = rep2.subject.properties.pop_size[1];
	return rep2.util.openSubWindow(url + '&popup=1', width, height, 0, 0);
};

// }}}
// {{{ rep2.subject.showMotoLsPopUp()

rep2.subject.showMotoLsPopUp = function (event, element) {
	showMotoLsPopUp(event, element, element.nextSibling.innerText)
};

// }}}
// {{{ rep2.subject.resizeTitleCell()

rep2.subject.resizeTitleCell = function () {
	var _ = rep2.subject;
	var w = $(window).width(), d = 0;
	var i, ss, sel, val;

	$.each($('table.threadlist > thead > tr').first().find('th'), function(){
		var self = $(this);
		w -= self.outerWidth();
		if (self.hasClass('tl')) {
			w += self.width();
			d++;
		}
	});

	ss = document.styleSheets[_.dynamicStyleIndex];
	sel = 'table.threadlist td.tl div.el';
	val = 'width: ' + Math.floor(w / d) + 'px';

	if (_.dynamicRuleIndex > -1) {
		i = _.dynamicRuleIndex;
		if (typeof ss.deleteRule !== 'undefined') {
			ss.deleteRule(i);
		} else if (typeof ss.removeRule !== 'undefined') {
			ss.removeRule(i);
		}
	} else {
		i = (ss.rules || ss.cssRules).length;
		_.dynamicRuleIndex = i;
	}

	if (typeof ss.addRule !== 'undefined') {
		ss.addRule(sel, val, i);
	} else {
		ss.insertRule(sel + ' { ' + val + '; }', i);
	}
};

// }}}
// {{{ rep2.subject.offRecent()

rep2.subject.offRecent = function (anchor) {
	var url = anchor.href.replace('info.php?', 'httpcmd.php?cmd=offrec&');
	$.get(url, null, function(text, status){
		if (status == 'error') {
			window.alert('Async error!');
		} else if (text === '0' || text === '') {
			window.alert('�����������s!');
		} else {
			var row = anchor.parentNode.parentNode;
			row.parentNode.removeChild(row);
		}
	});
	return false;
};

// }}}
// {{{ rep2.subject.setup()

rep2.subject.setup = function (group_number) {
	var _ = rep2.subject;
	var cells, set;

	if (typeof group_number === 'undefined') {
		cells = $('table.threadlist > tbody > tr > td');
	} else {
		cells = $('table.threadlist > tbody.tgroup' + group_number + ' > tr > td');
	}

	// URL����host-bbs-key�𒊏o���鐳�K�\��
	var re = /[\?&](host=.+?&bbs=.+?&key=.+?)(&|$)/;
	var host_bbs_key = function (anchor) {
		return re.exec(anchor.href)[1];
	};

	// �ŋߓǂ񂾃X������
	cells.filter('.tc').find('a[href$="&offrec=true"]').click(function(){
		return _.offRecent(this);
	});

	// ���E�C���h�E�\��
	cells.filter('.to').find('a.info').click(function(){
		return _.openSubWindow(this.href);
	});

	// ���O���폜
	set = cells.filter('.tu').find('a.un, a.un_a, a.un_n');
	set.attr('title', '�N���b�N����ƃ��O�폜');
	set.filter('.un_n').click(function(){
		if (!window.confirm('���O���폜���܂����H')) {
			return false;
		}
		return _.deleteLog(host_bbs_key(this), this);
	});
	set.filter('.un, .un_a').click(function(){
		return _.deleteLog(host_bbs_key(this), this);
	});

	// �͈͂��w�肵�Č��X�����J�����|�b�v�A�b�v���j���[
	var hover = function (event) {
		_.showMotoLsPopUp(event, this);
	};

	// �X���b�h�^�C�g���̕����F��ύX
	var click = function () {
		var id = this.id.substring(2);
		_.changeThreadTitleColor(id);
		if ($(this).hasClass('midoku_ari')) {
			_.changeUnReadColor(id);
		}
	};

	// ���X���ƃX���b�h�^�C�g��
	cells.filter('.tl').find('a').map(function(){
		var self = $(this);
		if (self.hasClass('moto_thre')) {
			self.hover(hover, hideMotoLsPopUp);
		} else {
			self.attr('title', self.text());
			self.click(click);
		}
	})

	// ���C�ɃX��
	set = cells.filter('.t').find('a.fav[href$="&setfav=0"]');
	set.attr('title', '���C�ɃX������O��');
	set.click(function () {
		return _.setFavorite(host_bbs_key(this), '0', this);
	});
	set = cells.filter('.t').find('a.fav[href$="&setfav=1"]');
	set.attr('title', '���C�ɃX���ɒǉ�');
	set.click(function(){
		return _.setFavorite(host_bbs_key(this), '1', this);
	});

	// IE�΍�
	/* jQuery3.x�ō폜���ꂽ�̂ŃR�����g�A�E�g
	if ($.browser.msie) {
		cells.contents().filter('[nodeType=3]').wrap('<span class="nowrap"></span>');
	}
	*/
};

// }}}
// {{{ $(document).ready()

$(document).ready(function(){
	var _ = rep2.subject;
	var i, n;

	_.dynamicStyleIndex = 0;
	_.dynamicRuleIndex = -1;
	n = document.styleSheets.length;
	for (i = 0; i < n; i++) {
		if (document.styleSheets[i].href.indexOf('css/blank.css') != -1) {
			_.dynamicStyleIndex = i;
			break;
		}
	}
	if (i == n) {
		i = 0;
	}

	$('#allbox').on('change', function() {
		$('.threadlist input:checkbox[name!=allbox]').prop('checked', this.checked);
	});

	_.setWindowTitle();
	_.resizeTitleCell();

	if (_.properties.threads_count > 300) {
		var j;
		i = 0;
		n = $('table.threadlist > tbody').length;
		while (i < n) {
			j = i + 1;
			window.setTimeout('rep2.subject.setup(' + j + ')', 100 * i + 1);
			i = j;
		}
	} else {
		_.setup();
	}
});

// }}}
// {{{ $(window).resize

$(window).resize(rep2.subject.resizeTitleCell);

// }}}

/*
 * Local Variables:
 * mode: javascript
 * coding: cp932
 * tab-width: 4
 * c-basic-offset: 4
 * indent-tabs-mode: t
 * End:
 */
/* vim: set syn=javascript fenc=cp932 ai noet ts=4 sw=4 sts=4 fdm=marker: */
