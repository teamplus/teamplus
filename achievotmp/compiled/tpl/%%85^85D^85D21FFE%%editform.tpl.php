<?php /* Smarty version 2.6.11, created on 2011-10-27 18:01:18
         compiled from ./atk/themes/basic/templates/editform.tpl */ ?>
<?php require_once(SMARTY_CORE_DIR . 'core.load_plugins.php');
smarty_core_load_plugins(array('plugins' => array(array('function', 'atktext', './atk/themes/basic/templates/editform.tpl', 8, false),)), $this); ?>
<br>
<table id="editform" width="100%">
  <?php if (( count ( $this->_tpl_vars['errors'] ) > 0 )): ?>
    <tr>
      <td colspan="2" class="error">
        <?php echo $this->_tpl_vars['errortitle']; ?>

        <?php $_from = $this->_tpl_vars['errors']; if (!is_array($_from) && !is_object($_from)) { settype($_from, 'array'); }if (count($_from)):
    foreach ($_from as $this->_tpl_vars['error']):
?>
          <br><?php echo $this->_tpl_vars['error']['label']; ?>
: <?php echo $this->_tpl_vars['error']['message']; ?>
 <?php if (isset ( $this->_tpl_vars['error']['tablink'] )): ?> (<?php echo smarty_function_atktext(array('0' => 'error_tab'), $this);?>
 <?php echo $this->_tpl_vars['error']['tablink']; ?>
)<?php endif; ?>
        <?php endforeach; endif; unset($_from); ?>
      </td>
    </tr>
  <?php endif; ?>
  <?php $_from = $this->_tpl_vars['fields']; if (!is_array($_from) && !is_object($_from)) { settype($_from, 'array'); }if (count($_from)):
    foreach ($_from as $this->_tpl_vars['field']):
?>
    <tr<?php if ($this->_tpl_vars['field']['rowid'] != ""): ?> id="<?php echo $this->_tpl_vars['field']['rowid']; ?>
"<?php endif;  if (! $this->_tpl_vars['field']['initial_on_tab']): ?> style="display: none"<?php endif; ?> class="<?php echo $this->_tpl_vars['field']['tab']; ?>
">
      <?php if (isset ( $this->_tpl_vars['field']['line'] )): ?>
        <td colspan="2" valign="top"><?php echo $this->_tpl_vars['field']['line']; ?>
</td>
      <?php else: ?>
      <?php if ($this->_tpl_vars['field']['label'] !== 'AF_NO_LABEL'): ?><td valign="top" class="<?php if (isset ( $this->_tpl_vars['field']['error'] )): ?>errorlabel<?php else: ?>fieldlabel<?php endif; ?>"><?php if ($this->_tpl_vars['field']['label'] != ""):  echo $this->_tpl_vars['field']['label']; ?>
 <?php if ($this->_tpl_vars['field']['obligatory'] != ""):  echo $this->_tpl_vars['field']['obligatory'];  endif; ?> : <?php endif; ?></td><?php endif; ?>
        <td valign="top" <?php if ($this->_tpl_vars['field']['label'] === 'AF_NO_LABEL'): ?>colspan="2"<?php endif; ?> class="field"><?php echo $this->_tpl_vars['field']['full']; ?>
</td>
      <?php endif; ?>
    </tr>
  <?php endforeach; endif; unset($_from); ?>
</table>