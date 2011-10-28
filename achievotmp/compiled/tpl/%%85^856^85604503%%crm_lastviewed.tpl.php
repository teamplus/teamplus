<?php /* Smarty version 2.6.11, created on 2011-10-27 18:00:05
         compiled from ./themes/default/templates/crm_lastviewed.tpl */ ?>
<?php require_once(SMARTY_CORE_DIR . 'core.load_plugins.php');
smarty_core_load_plugins(array('plugins' => array(array('function', 'atktext', './themes/default/templates/crm_lastviewed.tpl', 1, false),array('modifier', 'truncate', './themes/default/templates/crm_lastviewed.tpl', 3, false),)), $this); ?>
<b><?php echo smarty_function_atktext(array('id' => 'last_viewed','module' => 'crm'), $this);?>
:</b>&nbsp;
<?php $_from = $this->_tpl_vars['items']; if (!is_array($_from) && !is_object($_from)) { settype($_from, 'array'); }$this->_foreach['lastvieweditems'] = array('total' => count($_from), 'iteration' => 0);
if ($this->_foreach['lastvieweditems']['total'] > 0):
    foreach ($_from as $this->_tpl_vars['item']):
        $this->_foreach['lastvieweditems']['iteration']++;
?>
<a class="lastviewedlink" href="<?php echo $this->_tpl_vars['item']['url']; ?>
" accessKey="<?php echo $this->_foreach['lastvieweditems']['iteration']; ?>
" title="[Alt+<?php echo $this->_foreach['lastvieweditems']['iteration']; ?>
]"><?php echo ((is_array($_tmp=$this->_tpl_vars['item']['summary'])) ? $this->_run_mod_handler('truncate', true, $_tmp, 15, '', true) : smarty_modifier_truncate($_tmp, 15, '', true)); ?>
</a>
<?php if (($this->_foreach['lastvieweditems']['iteration'] == $this->_foreach['lastvieweditems']['total']) == false): ?>
&nbsp;|&nbsp;
<?php endif; ?>

<?php endforeach; endif; unset($_from); ?>