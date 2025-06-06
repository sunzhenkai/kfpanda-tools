# Description

Kung Fu Panda Tools.
Kung Fu Panda c++ sdk.

# Examples

## Replay

```shell
❯ ./build/kfpanda-tools replay --service=KungFuPandaServer --target='127.0.0.1:9820' --count=5  | jq
{
  "successCount": 5,
  "responses": [
    {
      "message": "hello world",
      "type": "RECORD_TYPE_HTTP",
      "typeStr": "RECORD_TYPE_HTTP"
    },
    {
      "message": "hello world",
      "type": "RECORD_TYPE_HTTP",
      "typeStr": "RECORD_TYPE_HTTP"
    },
    {
      "message": "hello world",
      "type": "RECORD_TYPE_HTTP",
      "typeStr": "RECORD_TYPE_HTTP"
    },
    {
      "message": "hello world",
      "type": "RECORD_TYPE_HTTP",
      "typeStr": "RECORD_TYPE_HTTP"
    },
    {
      "message": "hello world",
      "type": "RECORD_TYPE_HTTP",
      "typeStr": "RECORD_TYPE_HTTP"
    }
  ]
}
```
