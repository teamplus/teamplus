<?php /* Smarty version 2.6.11, created on 2011-10-27 18:00:48
         compiled from ./atk/themes/win2k/templates/top.tpl */ ?>
<table border="0" cellpadding="6" cellspacing="0" bgcolor="#FFFFFF" width="100%" align="center" valign="top">
  <tr>
    <td>
      <img src="<?php echo $this->_tpl_vars['themedir']; ?>
images/logo.gif" alt='' align=left>
    </td>
    <td align="center" class="block" >
      <table width="100%" bgcolor="#FFFFFF">
        <tr>
          <td align="left" width="20%"></td>
          <td align="center" width="60%">
            <br /><?php echo $this->_tpl_vars['logintext']; ?>
:
            <b><?php echo $this->_tpl_vars['user']; ?>
</b> &nbsp; <a href="<?php echo $this->_tpl_vars['logoutlink']; ?>
" target="<?php echo $this->_tpl_vars['logouttarget']; ?>
"><?php echo $this->_tpl_vars['logouttext']; ?>
</a> &nbsp;
			<?php if ($this->_tpl_vars['centerpiece']):  echo $this->_tpl_vars['centerpiece'];  endif; ?>
          </td>
          <td align="right" width="20%" nowrap><?php if ($this->_tpl_vars['searchpiece']):  echo $this->_tpl_vars['searchpiece']; ?>
</span><?php endif; ?></td>
        </tr>
      </table>
      <br/>
    </td>
  </tr>
</table>
<table border="0" cellpadding="0" cellspacing="0" width="100%">
  <tr><td bgcolor="#75736E" colspan="2" valign="top"><img src="<?php echo $this->_tpl_vars['themedir']; ?>
images/blank.gif" height="1" width="1"></td></tr>
  <tr><td bgcolor="#FFFFFF" colspan="2" valign="top"><img src="<?php echo $this->_tpl_vars['themedir']; ?>
images/blank.gif" height="1" width="1"></td></tr>
</table>