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

## Replay With Compare

```shell
❯ ./build/kfpanda-tools replay --service=KungFuPandaServer --target_base='127.0.0.1:9820' --target_compare='127.0.0.1:9820' -
-count=5 | jq
{
  "successCount": 5,
  "responses": [
    {
      "base": {
        "message": "hello world",
        "type": "RECORD_TYPE_HTTP",
        "typeStr": "RECORD_TYPE_HTTP"
      },
      "compare": {
        "message": "hello world",
        "type": "RECORD_TYPE_HTTP",
        "typeStr": "RECORD_TYPE_HTTP"
      }
    },
    {
      "base": {
        "message": "hello world",
        "type": "RECORD_TYPE_HTTP",
        "typeStr": "RECORD_TYPE_HTTP"
      },
      "compare": {
        "message": "hello world",
        "type": "RECORD_TYPE_HTTP",
        "typeStr": "RECORD_TYPE_HTTP"
      }
    },
    {
      "base": {
        "message": "hello world",
        "type": "RECORD_TYPE_HTTP",
        "typeStr": "RECORD_TYPE_HTTP"
      },
      "compare": {
        "message": "hello world",
        "type": "RECORD_TYPE_HTTP",
        "typeStr": "RECORD_TYPE_HTTP"
      }
    },
    {
      "base": {
        "message": "hello world",
        "type": "RECORD_TYPE_HTTP",
        "typeStr": "RECORD_TYPE_HTTP"
      },
      "compare": {
        "message": "hello world",
        "type": "RECORD_TYPE_HTTP",
        "typeStr": "RECORD_TYPE_HTTP"
      }
    },
    {
      "base": {
        "message": "hello world",
        "type": "RECORD_TYPE_HTTP",
        "typeStr": "RECORD_TYPE_HTTP"
      },
      "compare": {
        "message": "hello world",
        "type": "RECORD_TYPE_HTTP",
        "typeStr": "RECORD_TYPE_HTTP"
      }
    }
  ]
}
```
