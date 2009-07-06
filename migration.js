if (Drupal.jsEnabled) {
  $(document).ready(function() {
    $('#migration_start_monitor').click(function(){
      $.getJSON('/admin/settings/migration/start_monitor', function(json) {
        $('#migration_monitor_switch').html(json.divHtml);
        reapplyStopEvent();
        alert(json.response);
      });
    });
    $('#migration_stop_monitor').click(function(){
      $.getJSON('/admin/settings/migration/stop_monitor', function(json) {
        $('#migration_monitor_switch').html(json.divHtml);
        reapplyStartEvent();
        alert(json.response);
      });
    });
  })
  
  function reapplyStartEvent() {
    $('#migration_start_monitor').click(function(){
      $.getJSON('/admin/settings/migration/start_monitor', function(json) {
        $('#migration_monitor_switch').html(json.divHtml);
        reapplyStopEvent();
        alert(json.response);
      });
    });
  }
  
  function reapplyStopEvent() {
    $('#migration_stop_monitor').click(function(){
      $.getJSON('/admin/settings/migration/stop_monitor', function(json) {
        $('#migration_monitor_switch').html(json.divHtml);
        reapplyStartEvent();
        alert(json.response);
      });
    });
  }
  
}
