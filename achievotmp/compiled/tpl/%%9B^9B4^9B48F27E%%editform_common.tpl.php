<?php /* Smarty version 2.6.11, created on 2011-10-27 18:00:06
         compiled from ./atk/themes/achievo_modern/templates/editform_common.tpl */ ?>
<?php require_once(SMARTY_CORE_DIR . 'core.load_plugins.php');
smarty_core_load_plugins(array('plugins' => array(array('function', 'atktext', './atk/themes/achievo_modern/templates/editform_common.tpl', 7, false),)), $this); ?>
<table id="editform" border="0">
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
  <?php $_from = $this->_tpl_vars['fieldspart']; if (!is_array($_from) && !is_object($_from)) { settype($_from, 'array'); }if (count($_from)):
    foreach ($_from as $this->_tpl_vars['part']):
?>
    <?php echo $this->_tpl_vars['part']; ?>

  <?php endforeach; endif; unset($_from); ?>
</table>