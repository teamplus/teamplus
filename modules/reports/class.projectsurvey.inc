<?php

include_once (moduleDir("reports")."class.basereport.inc");

userelation("atkmanytoonerelation");

useattrib("atkdateattribute");
useattrib("atkboolattribute");
useattrib("atklistattribute");
useattrib("atkboolattribute");

class eventssurvey extends basereport
{
  public function __construct()
  {
    parent::basereport("eventssurvey");

    /**
     * Project - autocomplete field with a 'select' button to select from a list
     * In the autocomplete, I should be able to type a events name or a events number
     */
    $this->add(new atkManyToOneRelation("events","events.events", AF_MANYTOONE_AUTOCOMPLETE))
    ->setAutoCompleteSearchFields(array("name","abbreviation"));
    
    $this->add(new atkBoolAttribute("subevents"));

    /**
     * from/to dates; if set, will only show eventss/phases that 
     * have been worked on in that time frame.
     */
    $this->add(new atkDateAttribute("from"));
    $this->add(new atkDateAttribute("to"));

    /**
     * select only eventss/phases from this coordinator
     */
    $this->add(new atkManyToOneRelation("coordinator","employee.employee"));

    /**
     * select only eventss/phases that this person has booked time on
     */
    $this->add(new atkManyToOneRelation("worked_on_by","employee.employee"));

    /**
     * select eventss that match this description or phases that match
     * this description
     */
    $this->add(new atkAttribute("description",0,50));
    
    /**
     * We want to have default only active eventss/phases but
     * in the search criteria make it possible to search in only closed eventss or both
     */
    $this->add(new atkListAttribute("eventsstatus",array("active","nonactive","archived","all"),"",AF_LIST_NO_NULL_ITEM));
    $this->add(new atkListAttribute("phasestatus",array("active","nonactive","all"),"",AF_LIST_NO_NULL_ITEM));

    /**
     * ability to turn on/off columns (similar to hoursurvey)
     */
    $this->add(new atkMultiSelectAttribute("show_only_columns",
    array($this->text("events"), $this->text("phase"), $this->text("coordinator"),
    $this->text("startdate"), $this->text("enddate"), $this->text("first_hr"), $this->text("last_hr"),
    $this->text("initial_planning"), $this->text("current_planning"), $this->text("spend_hours")),
    array("events", "phase", "coordinator","startdate", "enddate", "first_hr", "last_hr",
    "initial_planning", "current_planning", "spend_hours"),4));
  }

  public function initial_values()
  {
    return array("show_only_columns"=>array("events", "phase", "coordinator","startdate", "enddate", "first_hr", "last_hr",
    "initial_planning", "current_planning", "spend_hours"),"eventsstatus"=>"active","phasestatus"=>"active","subevents"=>0);
  }
  
  public function events_selection($record, $mode)
  {
    /**
     * security: you can only select eventss that you are a coordinator of
     * unless you have 'all eventss' privilege. (I may change my mind later, if it's useful
     * for developers I might want to change this).
     */
    $node = &$this->getAttribute("events")->getDestination();
    if(!$node->allowed("any_events"))
    {
      $node->addFilter("events.coordinator='".atkGetUserId()."'");
    }
    return $this->getAttribute("events")->getSelectableRecords($record, $mode);
  }

  private function buildWhere($filterrecord)
  {
    $node = &atkGetNode("events.events");
    $where = '';
    
    if(!$node->allowed("any_events")) $where .= " WHERE p.coordinator='".atkGetUserId()."'";
    
    if(isset($filterrecord['events']['id']))
    {
      if(atkArrayNvl($filterrecord,'subevents'))
      {
        atkimport('modules.reports.utils.reportutils');
        $ids = reportutils::getProjectAndSubProjectId($filterrecord['events']['id']);
        $condition = "IN(".implode(",",$ids).")";
        $where .= ($where == "" ? " WHERE " : " AND ") . "p.id $condition";
      }
      else 
      {
        $where .= ($where == "" ? " WHERE " : " AND ") . "p.id = '".$filterrecord['events']['id']."'";
      }
    }
    
    if(!empty($filterrecord['from']))
    {
      $from = dateutil::arr2str($filterrecord["from"]);
      $where .= ($where == "" ? " WHERE " : " AND ") . "(t.startdate >= '$from' OR t.startdate IS NULL)";
    }
    
    if(!empty($filterrecord['to']))
    {
      $to = dateutil::arr2str($filterrecord["to"]);
      $where .= ($where == "" ? " WHERE " : " AND ") . "(t.enddate <= '$to' OR t.enddate IS NULL)";
    }
    
    if(isset($filterrecord['coordinator']['id']))
    {
      $where .= ($where == "" ? " WHERE " : " AND ") . "p.coordinator = '".$filterrecord['coordinator']['id']."'";
    }
    
    if(!empty($filterrecord['description']))
    {
      $where .= ($where == "" ? " WHERE " : " AND ") . "(LOWER(p.description) LIKE LOWER('%".$filterrecord['description']."%') 
        OR LOWER(t.description) LIKE LOWER('%".$filterrecord['description']."%'))";
    }
    
    if($filterrecord['eventsstatus']<>'all')
    {
      $where .= ($where == "" ? " WHERE " : " AND ") . "p.status = '".$filterrecord['eventsstatus']."'";
    }
    
    if($filterrecord['phasestatus']<>'all')
    {
      $where .= ($where == "" ? " WHERE " : " AND ") . "t.status = '".$filterrecord['phasestatus']."'";
    }
    return $where;
  }
  
  public function getContentElements($filterrecord)
  {
    /*@var $db atkDb*/
    $db = &$this->getDb();
    $node = &atkGetNode("events.events");

    /**
     * If I choose to hide the phase column, then it needs to just show 1 line per events, 
     * and the initial/current/actual should be the sum of the phases. I.o.w. if I have a 
     * 3-phase events, each with 50 hours, and I'm asking for a report on all my current 
     * eventss but not at the phase level, it should just show the events with 150 as planning.
     * 
     * We have to see first hour/last hour and start/end in both scenario's.
     * If we display only the events, it's the first and last hour booked on the
     * events. If we show all phases, then it's the first and last hour on the phase.
     * Same for the dates. 
     */
    $querystring = "
      SELECT"
    . (!in_array("events",$filterrecord['show_only_columns']) ? "" : " p.name events, p.id eventsid,")
    . (!in_array("phase",$filterrecord['show_only_columns']) ? "" : " t.name phase,t.id phaseid,")
    . (!in_array("coordinator",$filterrecord['show_only_columns']) ? "" : " CONCAT(IFNULL(c.lastname,''),' ',IFNULL(c.firstname,'')) coordinator,")
    . (!in_array("first_hr",$filterrecord['show_only_columns']) ? "" : " s.first_hr,")
    . (!in_array("last_hr",$filterrecord['show_only_columns']) ? "" : " s.last_hr,")
    . (!in_array("initial_planning",$filterrecord['show_only_columns']) ? "" : 
        (!in_array("phase",$filterrecord['show_only_columns']) ? " SUM(t.initial_planning) initial_planning," : " t.initial_planning,"))
    . (!in_array("current_planning",$filterrecord['show_only_columns']) ? "" :  
        (!in_array("phase",$filterrecord['show_only_columns']) ? " SUM(t.current_planning) current_planning," : " t.current_planning,"))
    . (!in_array("spend_hours",$filterrecord['show_only_columns']) ? "" : 
        (!in_array("phase",$filterrecord['show_only_columns']) ? " SUM(s.spend_hours) spend_hours," : " s.spend_hours,"))
    . (!in_array("phase",$filterrecord['show_only_columns']) ? 
        ((!in_array("startdate",$filterrecord['show_only_columns']) ? "" : " p.startdate,") 
       . (!in_array("enddate",$filterrecord['show_only_columns']) ? "" : " p.enddate,")) :
        ((!in_array("startdate",$filterrecord['show_only_columns']) ? "" : " t.startdate,") 
       . (!in_array("enddate",$filterrecord['show_only_columns']) ? "" : " t.enddate,")) )
    . "0 FROM
        events p
        JOIN phase t on p.id=t.eventsid
        LEFT JOIN person c on p.coordinator = c.id "
        . (isset($filterrecord['worked_on_by']['id']) ? "JOIN " : "LEFT JOIN ") . 
         "(SELECT 
            SUM(h.time) spend_hours,
            min(h.activitydate) first_hr,
            max(h.activitydate) last_hr,
            t.eventsid,
            h.userid,
            t.id phaseid
           FROM 
             hoursbase h JOIN phase t ON h.phaseid=t.id"
           . (isset($filterrecord['worked_on_by']['id']) ? " WHERE h.userid='".$filterrecord['worked_on_by']['id']."'" : "")
           . (!in_array("phase",$filterrecord['show_only_columns']) ? " GROUP BY t.eventsid" : " GROUP BY t.id")
           . ") s ON s.eventsid=p.id AND t.id=s.phaseid";

    //Build where condition
    $where = $this->buildWhere($filterrecord);
    
    //Build group condition
    $group = '';
    
    if(!in_array("phase",$filterrecord['show_only_columns']))
    {
      $group = " GROUP BY p.id";
    }
    
    $rows = $db->getrows($querystring.$where.$group);
    
    if(count($rows)==0) return array("eventssurvey_report"=>$this->text("empty_resultset"));

    /*@var $tr tableRenderer*/    
    $tr = &atknew("module.reports.utils.tablerenderer");
    $i=0;
    
    //Header
    foreach ($filterrecord['show_only_columns'] as $column)
    {
      $list[] = $this->text($column);
    }
    $recordset[] = $list;
    
    $totalinitial = $totalcurrent = $totalspend = 0;

    $action = null;
    if($node->allowed("edit")) $action = 'edit';
    elseif($node->allowed("view")) $action = 'view';
    
    $phase = &atkGetNode("events.phase");
    
    foreach ($rows as $r)
    {
      $row = array();

      if(array_key_exists('events',$r))
      {
        /**
         * Project should be a link to events edit (take security into account, 
         * not everyone is allowed to edit eventss; if not, use view, but also with security
         */
        if(empty($action))
        {
          $row[] = $r['events'];
        }
        else 
        {
          $row[] = href(dispatch_url("events.events",$action,array("atkselector"=>"events.id='".$r['eventsid']."'")), $r['events'], SESSION_NESTED);
        }
      }
      
      foreach (array('phase','coordinator','startdate','enddate','first_hr','last_hr') as $field)
      {
        if(array_key_exists($field, $r))
        {
          $row[] = $r[$field];
        }
      }
      
      if(array_key_exists('initial_planning',$r))
      {
        $row[] = time_format($r['initial_planning']);
        $totalinitial += $r['initial_planning'];
      }
      
      if(array_key_exists('current_planning', $r))
      {
        $row[] = time_format($r['current_planning']);
        $totalcurrent += $r['current_planning'];
      }
      
      if(array_key_exists('spend_hours',$r))
      {
        /**
         * Similar to events admin phase list, the 'actual' should be a link 
         * to the hoursurvey to view details.
         */
        $params["phaseid"] = "phase.id='".$r['phaseid']."'";
        $params["startdate"] = "2000-01-01";
        $params["enddate"] = date("Y-m-d");
        
        if(isset($filterrecord['worked_on_by']['id']))
        {
          $params["userid"] = $filterrecord['worked_on_by']['id'];
        }
        else
        {
          $params["userid"] = "all";
        }

        $row[] = atkHref(dispatch_url("reports.hoursurvey", "report", $params), time_format($r['spend_hours']), SESSION_NESTED);
        $totalspend += $r['spend_hours'];
      }
          
      /**
       * Row should be colored the same as in the events admin phase list
       */
      $color = $phase->rowColor($r);
      if($color)
      {
        $tr->setRowStyle($i+1,"background-color:$color");
      }
      
      $recordset[] = $row;
      $i++;
    }
    
    //Footer with totals
    $footer[] = $this->text("total").":";
    for($i=1,$_i=count($filterrecord['show_only_columns']); $i<$_i; $i++)
    {
      switch ($filterrecord['show_only_columns'][$i])
      {
        case 'initial_planning':
          $footer[] = time_format($totalinitial);
          $tr->setColAlignment($i,TBL_RIGHT);
          break;
        case 'current_planning':
          $footer[] = time_format($totalcurrent);
          $tr->setColAlignment($i,TBL_RIGHT);
          break;
        case 'spend_hours':
          $footer[] = time_format($totalspend);
          $tr->setColAlignment($i,TBL_RIGHT);
          break;
        default:
          $footer[]="";
          break; 
      }
    }
    $recordset[] = $footer;
    
    $list = $tr->render($recordset, TBL_DATA|TBL_FOOTER, "recordlist");

    return array("eventssurvey_report"=>$list);
  }

}