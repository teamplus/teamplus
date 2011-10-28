<?php /* Smarty version 2.6.11, created on 2011-10-27 18:00:06
         compiled from ./atk/themes/achievo_modern/templates/tabs.tpl */ ?>
<?php require_once(SMARTY_CORE_DIR . 'core.load_plugins.php');
smarty_core_load_plugins(array('plugins' => array(array('function', 'atkthemeimg', './atk/themes/achievo_modern/templates/tabs.tpl', 5, false),)), $this); ?>
<script language="JavaScript" type="text/javascript">
var tabs = new Array();
<?php unset($this->_sections['i']);
$this->_sections['i']['name'] = 'i';
$this->_sections['i']['loop'] = is_array($_loop=$this->_tpl_vars['tabs']) ? count($_loop) : max(0, (int)$_loop); unset($_loop);
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
?>tabs[tabs.length] = "<?php echo $this->_tpl_vars['tabs'][$this->_sections['i']['index']]['tab']; ?>
"; <?php endfor; endif; ?>

var tabLeftImage = "<?php echo smarty_function_atkthemeimg(array('0' => "tab_left.png"), $this);?>
";
var tabRightImage = "<?php echo smarty_function_atkthemeimg(array('0' => "tab_right.png"), $this);?>
";
var tabBackgroundImage = "<?php echo smarty_function_atkthemeimg(array('0' => "tab_back.png"), $this);?>
";
var tabSelectedLeftImage = "<?php echo smarty_function_atkthemeimg(array('0' => "tab_left_s.png"), $this);?>
";
var tabSelectedRightImage = "<?php echo smarty_function_atkthemeimg(array('0' => "tab_right_s.png"), $this);?>
";
var tabSelectedBackgroundImage = "<?php echo smarty_function_atkthemeimg(array('0' => "tab_back_s.png"), $this);?>
";

var tabColor = "#FFFFFF";
var tabSelectedColor = "#000000";
</script>

<div class="tabOuterDiv">
<table border="0" cellpadding="0" cellspacing="0" id="tabContainer">
  <tr>
  <?php unset($this->_sections['i']);
$this->_sections['i']['name'] = 'i';
$this->_sections['i']['loop'] = is_array($_loop=$this->_tpl_vars['tabs']) ? count($_loop) : max(0, (int)$_loop); unset($_loop);
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
  <td valign="bottom">

  <div class="tabInnerDiv">

  <div id="tab_<?php echo $this->_tpl_vars['tabs'][$this->_sections['i']['index']]['tab']; ?>
" style="position: absolute;">

    <table border="0" cellspacing="0" cellpadding="0">
      <tr onclick="showTab('<?php echo $this->_tpl_vars['tabs'][$this->_sections['i']['index']]['tab']; ?>
')">
        <td height="22" valign="middle" align="center" nowrap class="tabOn">
          <span style="color: #ff0000;"><?php echo $this->_tpl_vars['tabs'][$this->_sections['i']['index']]['title']; ?>
</span>
        </td>
      </tr>
    </table>

  </div>

  <table border="0" cellspacing="0" cellpadding="0" style="cursor: pointer;">
    <tr onclick="showTab('<?php echo $this->_tpl_vars['tabs'][$this->_sections['i']['index']]['tab']; ?>
')">
      <td height="22" valign="middle" align="center" nowrap class="tabOff">
        <?php echo $this->_tpl_vars['tabs'][$this->_sections['i']['index']]['title']; ?>

      </td>
    </tr>
   </table>

   </div>

   </td>

   <?php endfor; endif; ?>

 </tr>
</table>
</div>

<div id="tabContent">
  <?php echo $this->_tpl_vars['content']; ?>

</div>