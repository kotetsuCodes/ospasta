{
  "targets": [
    {
      "target_name": "copypasta",
      "sources": [ "copypasta.cc" ],
      
      'conditions': [
          ['OS == "mac"', {
            'include_dirs': [
              'System/Library/Frameworks/Carbon.Framework/Headers',
              'System/Library/Frameworks/ApplicationServices.framework/Headers',
            ],
            'link_settings': {
              'libraries': [
                '-framework Carbon',
                '-framework ApplicationServices',
              ]
            }
          }],
          ["OS=='win'", {
            'defines': ['IS_WINDOWS']
          }]
      ]
    }
  ]
}