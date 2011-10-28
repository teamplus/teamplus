<?php /* Smarty version 2.6.11, created on 2011-10-27 18:00:25
         compiled from ./atk/themes/winxp/templates/top.tpl */ ?>
<?php require_once(SMARTY_CORE_DIR . 'core.load_plugins.php');
smarty_core_load_plugins(array('plugins' => array(array('function', 'atkconfig', './atk/themes/winxp/templates/top.tpl', 4, false),)), $this); ?>
<table border="0" cellpadding="6" cellspacing="0" bgcolor="#FFFFFF" width="100%" align="center" valign="top" height="75">
  <tr>
    <td>
      <?php echo smarty_function_atkconfig(array('var' => 'theme_logo','smartyvar' => 'theme_logo'), $this);?>

      <?php if ($this->_tpl_vars['theme_logo'] != ''): ?><img src="<?php echo $this->_tpl_vars['theme_logo']; ?>
" alt='' align=left><?php else: ?>Update your configuration to put your logo here<?php endif; ?>
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
			    <?php if ($this->_tpl_vars['centerpiece']):  echo $this->_tpl_vars['centerpiece'];  endif; ?></td>
          <td align="right" width="20%" nowrap><?php if ($this->_tpl_vars['searchpiece']):  echo $this->_tpl_vars['searchpiece']; ?>
</span><?php endif; ?></td>
        </tr>
      </table><br/>
    </td>
  </tr>
</table>