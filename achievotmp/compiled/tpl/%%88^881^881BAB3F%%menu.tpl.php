<?php /* Smarty version 2.6.11, created on 2011-10-27 18:00:24
         compiled from ./atk/themes/winxp/templates/menu.tpl */ ?>
<script type="text/javascript" src="<?php echo $this->_tpl_vars['themedir']; ?>
javascript/menu.js"></script>

<script language="javascript">
  var panename  = new Array();
  var panestate = new Array();
</script>

<div id="dhtmlgoodies_xpPane">
<?php $_from = $this->_tpl_vars['menuitems']; if (!is_array($_from) && !is_object($_from)) { settype($_from, 'array'); }if (count($_from)):
    foreach ($_from as $this->_tpl_vars['menuitem']):
?>
  <?php if ($this->_tpl_vars['menuitem']['enable']): ?>
    <script language="javascript">
      <?php if ($this->_tpl_vars['menuitem']['url']): ?>
        panename[panename.length] = '<a href="<?php echo $this->_tpl_vars['menuitem']['url']; ?>
" target="main"><?php echo $this->_tpl_vars['menuitem']['name']; ?>
</a>';
      <?php else: ?>
        panename[panename.length] = '<?php echo $this->_tpl_vars['menuitem']['name']; ?>
';
      <?php endif; ?> 
      panestate[panestate.length] = false;
    </script>
  	<div class="dhtmlgoodies_panel">
  		<div>
  		  <?php unset($this->_sections['i']);
$this->_sections['i']['name'] = 'i';
$this->_sections['i']['loop'] = is_array($_loop=$this->_tpl_vars['menuitem']['submenu']) ? count($_loop) : max(0, (int)$_loop); unset($_loop);
$this->_sections['i']['show'] = true;
$this->_sections['i']['max'] = $this->_sections['i']['loop'];
$this->_sections['i']['step'] = 1;
$this->_sections['i']['start'] = $this->_sections['i']['step'] > 0 ? 0 : $this->_sections['i']['loop']-1;
if ($this->_sections['i']['show']) {
    $this->_sections['i']['total'] = $this->_sections['i']['loop'];
    if ($this->_sections['i']['total'] == 0)
        $this->_sections['i']['show'] = false;
} else
    $this->_sections['i']['total'] = 0;
if ($this->_sections['i']['show']):

            for ($this->_sections['i']['index'] = $this->_sections['i']['start'], $this->_sections['i']['iteration'] = 1;
                 $this->_sections['i']['iteration'] <= $this->_sections['i']['total'];
                 $this->_sections['i']['index'] += $this->_sections['i']['step'], $this->_sections['i']['iteration']++):
$this->_sections['i']['rownum'] = $this->_sections['i']['iteration'];
$this->_sections['i']['index_prev'] = $this->_sections['i']['index'] - $this->_sections['i']['step'];
$this->_sections['i']['index_next'] = $this->_sections['i']['index'] + $this->_sections['i']['step'];
$this->_sections['i']['first']      = ($this->_sections['i']['iteration'] == 1);
$this->_sections['i']['last']       = ($this->_sections['i']['iteration'] == $this->_sections['i']['total']);
?>
  		    <?php if ($this->_tpl_vars['menuitem']['submenu'][$this->_sections['i']['index']]['enable']): ?>
  		      <a href="<?php echo $this->_tpl_vars['menuitem']['submenu'][$this->_sections['i']['index']]['url']; ?>
" target="main"><?php echo $this->_tpl_vars['menuitem']['submenu'][$this->_sections['i']['index']]['name']; ?>
</a><br/>
  		    <?php endif; ?>
  		  <?php endfor; endif; ?>
      </div>
    </div>
  <?php endif;  endforeach; endif; unset($_from); ?> 
</div>

<script type="text/javascript">
/*
Arguments to function
1) Array of titles
2) Array indicating initial state of panels(true = expanded, false = not expanded )
*/
initDhtmlgoodies_xpPane(panename,panestate,Array(), '<?php echo $this->_tpl_vars['themedir']; ?>
');
</script>