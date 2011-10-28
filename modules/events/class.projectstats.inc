<?php

require_once(atkconfig("atkroot")."atk/utils/adodb-time.inc.php");

class eventsstats extends atkNode
{
  var $m_viewstart = "";
  var $m_viewend = "";
  var $m_zoom = "";
  var $m_eventsid = "";
  var $m_resolution = "";

  function eventsstats()
  {
    $sessionManager = &atkGetSessionManager();
    $this->atkNode("eventsstats", NF_READONLY);

    $this->m_viewstart = $sessionManager->stackVar("viewstart");

    if ($this->m_viewstart=="")
    {
      $this->m_viewstart = date("Y-m-d",adodb_mktime(0,0,0,date("m")-1,date("d"),date("Y")));
    }
    else if (is_array($this->m_viewstart))
    {
      $this->m_viewstart = sprintf("%04d-%02d-%02d", $this->m_viewstart["year"],
      $this->m_viewstart["month"],
      $this->m_viewstart["day"]);
    }

    $this->m_viewend = $sessionManager->stackVar("viewend");
    if ($this->m_viewend=="")
    {
      $this->m_viewend = date("Y-m-d");
    }
    else if (is_array($this->m_viewend))
    {
      $this->m_viewend = sprintf("%04d-%02d-%02d", $this->m_viewend["year"],
      $this->m_viewend["month"],
      $this->m_viewend["day"]);
    }

    $this->m_zoom = $sessionManager->stackVar("zoom");

    $this->m_eventsid = $sessionManager->stackVar("eventsid");

    $this->m_resolution = $sessionManager->stackVar("resolution");
    if ($this->m_resolution=="") $this->m_resolution = "auto";

    $this->setSecurityAlias("events.events");
  }

  function action_stats(&$handler)
  {
    include_once("achievotools.inc");

    $ui = &$this->getUi();
    $page = &$this->getPage();
    $this->addStyle("style.css");

    $startdate = $this->m_viewstart;
    $enddate = $this->m_viewend;
    $eventsid = $this->m_eventsid;

    $prjnode = &atkGetNode("events.events");

    $descriptor="";
    if ($eventsid!="")
    {
      // Get descriptor.
      $recs = $prjnode->selectDb("events.id=".$eventsid, "", "", "", $prjnode->descriptorFields());
      $descriptor = " - ".$prjnode->descriptor($recs[0]);
    }


    $backbtn = "";
    if (atkLevel()>0)
    {
      $backbtn = '<br><form method="get">'.session_form(SESSION_BACK).
      '<input type="submit" value="&lt;&lt; '.atkText('back','atk').'"></form>';
    }

    $output=$backbtn;

    if ($this->m_eventsid=="")
    {
      $output.= "<br>".$this->topProjects($startdate, $enddate, ($this->m_zoom=="topeventss"?0:10));

      $params["startdate"] = $startdate;
      $params["enddate"] = $enddate;
      $params["max"] = ($this->m_zoom=="topeventss"?20:10);
      $max = ($this->m_zoom=="topeventss"?0:10);
      useattrib("graph.dataGraphAttribute");

      $db = &atkGetDb();

      $query = &$db->createQuery();
      $query->addTable("hours");
      $query->addJoin("phase", "", "phase.id = hours.phaseid", false);
      $query->addJoin("events", "", "phase.eventsid = events.id", false);
      $query->addField("events.name");
      $query->addField("events.id");
      $query->addField("sum(time) as totaltime");
      $query->addCondition("hours.activitydate BETWEEN '".$startdate."' AND '".$enddate."'");
      if ($max)
      {
        $query->setLimit(0,$max);
      }
      $query->addOrderBy("totaltime DESC");
      $query->addGroupBy("events.name");
      $eventss = $db->getrows($query->buildSelect());

      for ( $i=0; $i < count($eventss); $i=$i+20 )
      {
        $params["from"] = ($this->m_zoom=="topeventss"?$i:0);
        $topProjects = &new dataGraphAttribute("topeventssdistribution", "topeventss", $params, "pie");
        $topProjects->setSource("events.events");
        atkdebug("<H1>DRAWING TOPPROJECTS!</H1>");

        $output.= "<br>".$topProjects->showGraph();
      }
    }
    else
    {

      $params["eventsid"] = $eventsid;
      $params["viewstart"] = $startdate;
      $params["viewend"] = $enddate;
      $params["resolution"] = $this->m_resolution;

      $detailparams["eventsid"] = $eventsid;
      $detailparams["startdate"] = $startdate;
      $detailparams["enddate"] = $enddate;
      $detailparams["userid"] = "all";

      useattrib("graph.dataGraphAttribute");


      // TIMELINE
      $timeline = &new dataGraphAttribute("timeline", "timeline", $params, "line");
      $timeline->setSource("events.events");
      $timeline->addDynamicParam("resolution", array("day", "week", "month", "auto"));

      $output.= "<br>".$timeline->showGraph();

      // PHASE STATS
      $phasestats = &new dataGraphAttribute("phasetimedistribution", "phasetime", $params, "auto");
      $phasestats->setSource("events.events");

      $output.= "<br>".$phasestats->showGraph();

      // Textual version:
      $output.= "<br><br>".$this->_tableStats(atkText("phase","events"), $prjnode->graph_phasetime($params, true), array("name"), $detailparams, "phaseid");

      // EMPLOYEE STATS
      $empstats = &new dataGraphAttribute("emptimedistribution", "emptime", $params, "auto");
      $empstats->setSource("events.events");

      $output.= "<br><br>".$empstats->showGraph();

      // Textual version:
      $output.= "<br><br>".$this->_tableStats(atkText("employee","events"), $prjnode->graph_emptime($params, true), array("firstname", "lastname"), $detailparams, "userid");

      // ACTIVITY STATS
      $activitystats = &new dataGraphAttribute("activitytimedistribution", "activitytime", $params, "auto");
      $activitystats->setSource("events.events");

      $output.= "<br><br>".$activitystats->showGraph();

      // Textual version:
      $output.= "<br><br>".$this->_tableStats(atkText("activity","events"), $prjnode->graph_activitytime($params, true), array("name"), $detailparams, "activity_id");

      // DOW STATS
      $dowstats = &new dataGraphAttribute("dowtimedistribution", "dowtime", $params, "auto");
      $dowstats->setSource("events.events");

      $output.= "<br><br>".$dowstats->showGraph();

      // Textual version:
      $output.= "<br><br>".$this->_tableStats(atkText("day","events"), $prjnode->graph_dowtime($params, true), array("dow"), $detailparams);
    }

    $output.="<br>".$backbtn."<br>";

    $boxes = array(
      $ui->renderBox(array("title"=>atkText("parameters","events"),"content"=>$this->navigator())),
      $ui->renderBox(array("title"=>atkText("stats","events").$descriptor,"content"=>$output)),
    );
    $actionpage = $this->renderActionPage("stats", $boxes);
    $page->addContent($actionpage);

  }

  function _paramForm($contents)
  {
    return '<form method="get">'.session_form().$contents.
    '<input type="submit" value="'.atkText('refresh','events').'"></form>';
  }

  function navigator()
  {
    useattrib("atkdateattribute");
    $startdate = $this->m_viewstart;
    $enddate = $this->m_viewend;
    $dummyrec = array("viewstart"=>array("year"=>substr($startdate,0,4),
    "month"=>substr($startdate,5,2),
    "day"=>substr($startdate,8,2)),
    "viewend"=>array("year"=>substr($enddate,0,4),
    "month"=>substr($enddate,5,2),
    "day"=>substr($enddate,8,2)));

    $startdateatt = new atkDateAttribute("viewstart","","", 0, date("Ymd"));
    $enddateatt = new atkDateAttribute("viewend","","", 0, date("Ymd"));

    $output = '<form action="'.getDispatchFile().'" method="get">';
    $output.= session_form();
    $output.= '<input type="hidden" name="atknodetype" value="'.$this->atkNodeType().'">';
    $output.= '<input type="hidden" name="atkaction" value="'.$this->m_action.'">';

    $output.= atkText("timespan","events").': '.$startdateatt->edit($dummyrec).' &nbsp;'.
    atkText("until","events").'&nbsp; '.$enddateatt->edit($dummyrec);

    $output.= ' &nbsp;<input type="submit" value="'.atkText("refresh","events").'">';

    $output.= '</form>';
    return $output;
  }

  function topProjects($start, $end, $max=0)
  {
    $db = &atkGetDb();
    atkdebug("niet in graph maar in topeventss");
    $query = &$db->createQuery();

    $query->addTable("hours");
    $query->addJoin("phase", "", "phase.id = hours.phaseid", false);
    $query->addJoin("events", "", "phase.eventsid = events.id", false);
    $query->addField("events.name");
    $query->addField("events.id");
    $query->addField("sum(time) as totaltime");
    $query->addCondition("hours.activitydate BETWEEN '".$start."' AND '".$end."'");
    if ($max)
    {
      $query->setLimit(0,$max);
    }
    $query->addOrderBy("totaltime DESC");
    $query->addGroupBy("events.name");
    $eventss = $db->getrows($query->buildSelect());

    if ($max)
    {
      $output ="<b>".sprintf(atkText("top_eventss","events"), $max).'</b> (';
      $output.=href(dispatch_url($this->atkNodeType(), "stats", array("zoom"=>"topeventss")), atkText("complete_list","events"));
    }
    else
    {
      $output ="<b>".atkText("alleventss","events").'</b> (';
      $output.=href(dispatch_url($this->atkNodeType(), "stats", array("zoom"=>"0")), sprintf(atkText("top_eventss","events"), 10));
    }
    $output.=')<br><br>';

    $data = array();
    // Add header
    $data[] = array("#",atkText("events","events"),atkText("time","events"));
    // Create data
    for ($i=0, $_i=count($eventss); $i<$_i; $i++)
    {
       $row = array();
       $row[]=($i+1);
       $row[]=href(dispatch_url($this->atknodetype(),$this->m_action,array("eventsid"=>$eventss[$i]["id"])),
                   $eventss[$i]["name"],
                   SESSION_NESTED);
       $row[] = time_format($eventss[$i]["totaltime"], true);
       $data[] = $row;
    }

    $tbl = &atknew("atk.utils.atktablerenderer");
    $tbl->setColAlignment(2,TBL_RIGHT);
    $output.=$tbl->render($data, TBL_DATA, "recordlist");
    return $output;
  }

  function _tableStats($itemheader, $dataset, $datasetdescriptors, $detailparams, $idparam="")
  {
    $securityManager = &atkGetSecurityManager();

    // Totals count
    $total = 0;
    for($i=0, $_i=count($dataset); $i<$_i; $i++)
    {
      $total+=$dataset[$i]["total"];
    }

    $mayviewdetail = ($idparam!="" && $securityManager->allowed("reports.hoursurvey", "view_all"));

    $data = array();
    // Add header
    $data[] = array($itemheader,
                    atkText("time","events"),
                    atkText("percentage","events"));
    if($mayviewdetail) $data[0][] = atkText("details","events");

    atkimport("atk.layout");
    $layout = &layout::getInstance();



    for($i=0, $_i=count($dataset); $i<$_i; $i++)
    {
      $row = array();

      $descriptor = array();
      // datasetdescriptors is an array contain information on which fields in $dataset are
      // the descriptors.
      foreach($datasetdescriptors as $field)
      {
        $descriptor[] = $dataset[$i][$field];
      }
      $value = $dataset[$i]["total"];

      $row[] = implode(" ",$descriptor);
      $row[] = time_format($value, true); // align right
      $percentage = ($total<=0?0:(($value/$total)*100));
      $row[] = sprintf("%02.02f", $percentage)."%"; // align right
      if ($mayviewdetail)
      {
        $detailparams[$idparam] = $dataset[$i]["id"];
        $detailurl = href(dispatch_url("reports.hoursurvey", "report", $detailparams), atkText("view","events"), SESSION_NESTED);
        $row[] = $detailurl;
      }
      $data[] = $row;
    }

    // Add Footer
    $footer = array(atkText("total","events"),time_format($total, true), '100.00%');
    if($mayviewdetail) $footer[] = "";
    $data[] = $footer;

    $tbl = &atknew("atk.utils.atktablerenderer");
    $tbl->setColAlignment(1,TBL_RIGHT);
    $tbl->setColAlignment(2,TBL_RIGHT);

    $res = $tbl->render($data, TBL_DATA|TBL_FOOTER, "recordlist");
    return $res;
  }
}

?>