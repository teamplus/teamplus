<?php /* Smarty version 2.6.11, created on 2011-10-27 18:01:03
         compiled from ./atk/themes/outlook/templates/top.tpl */ ?>
<div style="padding: 4px;">
<table border="0" cellpadding="0" cellspacing="0" bgcolor="#606060" width="100%" align="center">
  <tr>
    <td width="100%">
      <table width="100%" border="0" cellpadding="0" cellspacing="0" bgcolor="#00309C">
        <tr>
          <td width="12" align="left" bgcolor="#D5E8F4" background="<?php echo $this->_tpl_vars['themedir']; ?>
images/left.gif">&nbsp;</td>
          <td height="22" bgcolor="#0073CE" background="<?php echo $this->_tpl_vars['themedir']; ?>
images/dark_back.gif" valign="middle" align="left" nowrap>
            <b><small style="color:#ffffff;font-size:9pt"><img src="<?php echo $this->_tpl_vars['themedir']; ?>
images/publixheader.gif" border="0" alt="">&nbsp;<?php echo $this->_tpl_vars['title']; ?>
</small></b>
          </td>
          <td width="12" align="right" bgcolor="#D5E8F4" background="<?php echo $this->_tpl_vars['themedir']; ?>
images/right.gif">&nbsp;</td>
        </tr>
      </table>
      <table width="100%" border="0" cellpadding="9" cellspacing="2" bgcolor="#00309C">
        <tr>
          <td bgcolor="#EEEEE0" align="center" class="block">
<table width="100%"><tr>
  <td align="left" width="20%"></td>
  <td align="center" width="60%">
    <?php echo $this->_tpl_vars['logintext']; ?>
: <b><?php echo $this->_tpl_vars['user']; ?>
</b> &nbsp;
    <a href="<?php echo $this->_tpl_vars['logoutlink']; ?>
" target="<?php echo $this->_tpl_vars['logouttarget']; ?>
"><?php echo $this->_tpl_vars['logouttext']; ?>
</a> &nbsp;
    <?php if ($this->_tpl_vars['centerpiece']):  echo $this->_tpl_vars['centerpiece'];  endif; ?>
  </td>
  <td align="right" width="20%" nowrap><?php if ($this->_tpl_vars['searchpiece']):  echo $this->_tpl_vars['searchpiece']; ?>
</span><?php endif; ?></td>
</tr></table>
          </td>
        </tr>
      </table>
   </td>
 </tr>
</table>
</div>
<br>