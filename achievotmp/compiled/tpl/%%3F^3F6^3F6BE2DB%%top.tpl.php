<?php /* Smarty version 2.6.11, created on 2011-10-27 18:01:10
         compiled from ./atk/themes/macoslike/templates/top.tpl */ ?>
<table border="0" cellpadding="0" cellspacing="0" bgcolor="#606060" width="98%" align="center" valign="top">
  <tr>
    <td width="100%">
      <table width="100%" border="0" cellpadding="0" cellspacing="0" bgcolor="#00309C">
        <tr width="100%">
          <td width="12" align=left bgcolor="#d5d5d5" background="<?php echo $this->_tpl_vars['themedir']; ?>
images/left.gif">&nbsp;</td>
          <td height=22 bgcolor="#0073CE" background="<?php echo $this->_tpl_vars['themedir']; ?>
images/dark_back.gif" valign="middle" align="left" nowrap>
            <B><small style="color:#666666;font-size:9pt"><img src="<?php echo $this->_tpl_vars['themedir']; ?>
images/publixheader.gif" border=0>&nbsp;<?php echo $this->_tpl_vars['title']; ?>
</small></B>
          </td>
          <td width="12" align="right" bgcolor="#d5d5d5" background="<?php echo $this->_tpl_vars['themedir']; ?>
images/right.gif">&nbsp;</td>
        </tr>
      </table>
      <table width="100%" border="0" cellpadding="2" cellspacing="2" bgcolor="#efefef">
        <tr>
          <td bgcolor="#efefef" align="center" class="block">
			<table width="100%">
			  <tr>
			    <td align="left" width="20%"></td>
			    <td align="center" width="60%"><br /><?php echo $this->_tpl_vars['logintext']; ?>
:
<b><?php echo $this->_tpl_vars['user']; ?>
</b> &nbsp; <a href="<?php echo $this->_tpl_vars['logoutlink']; ?>
" target="<?php echo $this->_tpl_vars['logouttarget']; ?>
"><?php echo $this->_tpl_vars['logouttext']; ?>
</a> &nbsp;
			    <?php if ($this->_tpl_vars['centerpiece']):  echo $this->_tpl_vars['centerpiece'];  endif; ?></td>
                <td align="right" width="20%" nowrap><?php if ($this->_tpl_vars['searchpiece']):  echo $this->_tpl_vars['searchpiece']; ?>
</span><?php endif; ?></td>
              </tr>
            </table><br/>
          </td>
        </tr>
      </table>
   </td>
 </tr>
</table>
<br>