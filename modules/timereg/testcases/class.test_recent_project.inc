<?php
class test_recent_events extends atkTestCase  
{
  /**
   * Inside the constructor we register the fixtures we
   * want to use inside this test-case. 
   */
  public function __construct()
  {
    parent::atkTestCase();
    
    $this->addFixture('timereg.person');
    $this->addFixture('timereg.hoursbase');
    $this->addFixture('timereg.events');
    $this->addFixture('timereg.phase');
    $this->addFixture('timereg.events_person');
    $this->addFixture('timereg.accessright');
  }
  
  public function skip()
  {
    $this->skipIf(!$this->useTestDatabase() && $this->useFixture(),'Test database isn\'t configured');
  }
  
  
  public function setUp()
  {
    parent::setUp();
    
    atkimport("atk.security.atkmocksecuritymanager");
    $this->setMockSecurityManager(new atkMockSecurityManager());
  }
  
  public function tearDown()
  {
    parent::tearDown();
    $this->restoreSecurityManager();  
  }
  
  /**
   * Test if there are only two employees in the database.
   */
  public function test_recentProject()
  {
    useattrib("events.eventsmanytoonerelation");
    atkimport("module.events.events");
    $events = &new eventsManyToOneRelation("eventsid","events.events");
    
    $mockmgr = &atkGetSecurityManager();
      
    $mockmgr->setAllowed(true);
    $events->setUserId(1); //

    $ids = $this->filter($events->getRecentProjectsIds());
    $this->assertEqual($ids, array(19,28,27,26,25,24,23,22,21,20));

    $ids = $this->filter($events->getRecentProjectsIds(28));
    $this->assertEqual($ids, array(19,28,27,26,25,24,23,22,21,20));

    $ids = $this->filter($events->getRecentProjectsIds(30));
    $this->assertEqual($ids, array(30,19,28,27,26,25,24,23,22,21,20));
    
    $events->setUserId(2); 
    $mockmgr->setAllowed(false);

    $ids = $this->filter($events->getRecentProjectsIds());
    $this->assertEqual($ids, array(20,19));

    $ids = $this->filter($events->getRecentProjectsIds(30));
    $this->assertEqual($ids, array(30,20,19));
  }
  
  function filter($arr)
  {
    $res =  array();
    foreach ($arr as $key=>$value)
    {
      $res[] = $value['id'];
    }
    return $res;
  }

}
?>