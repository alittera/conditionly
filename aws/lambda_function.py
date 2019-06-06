import json
import boto3
from boto3.dynamodb.conditions import Key, Attr
from botocore.exceptions import ClientError


def lambda_handler(event, context):

    #Accessing DB 
    dynamodb = boto3.client('dynamodb')

    response = dynamodb.scan(TableName='conditionly')

    data = response['Items']
    maxid = 0
    maxtemp = 0

    print("Data:", data)
    # Scan table to check for the latest command
    for item in data:
        currentid = item["id"]["N"]
        currenttemp = item["temp"]["N"]
        if(int(currentid) > maxid):
            maxid = int(currentid)
            maxtemp = currenttemp


    db_response = dynamodb.get_item(TableName='conditionly', Key={'id':{'N': str(maxid)}, 'temp':{'N': str(maxtemp)}})

    #Found an item corresponding to the id requested
    item = db_response['Item']

    temp = item["temp"]["N"]
    fan = item["fan"]["N"]
    mode = item["mode"]["N"]
    power = item["power"]["BOOL"]
    swingLR = item["swingLR"]["BOOL"]
    swing = item["swing"]["BOOL"]

    print("Found cmd:", temp)

    #Preparing the response for Nucleo board
    response = {
        "power":power,
        "mode":int(mode),
        "fan":int(fan),
        "swing":swing,
        "swingLR":swingLR,
        "temp":int(temp)
    }

    return response
