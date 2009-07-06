if (Drupal.jsEnabled) {
  $(document).ready(function() {
    $('#migration-start-monitor').click(function() {
      $.getJSON(Drupal.settings.basePath + 'migration/start', function(json) {
        $('#migration-monitor-switch').html(json.divHtml);
        reapplyStopEvent();
        alert(json.response);
      });
      return false;
    });

    $('#migration-stop-monitor').click(function() {
      $.getJSON(Drupal.settings.basePath + 'migration/stop', function(json) {
        $('#migration-monitor-switch').html(json.divHtml);
        reapplyStartEvent();
        alert(json.response);
      });
      return false;
    });
  })
  
  function reapplyStartEvent() {
    $('#migration-start-monitor').click(function() {
      $.getJSON(Drupal.settings.basePath + 'migration/start', function(json) {
        $('#migration-monitor-switch').html(json.divHtml);
        reapplyStopEvent();
        alert(json.response);
      });
      return false;
    });
  }
  
  function reapplyStopEvent() {
    $('#migration-stop-monitor').click(function() {
      $.getJSON(Drupal.settings.basePath + 'migration/stop', function(json) {
        $('#migration-monitor-switch').html(json.divHtml);
        reapplyStartEvent();
        alert(json.response);
      });
      return false;
    });
  }
}
