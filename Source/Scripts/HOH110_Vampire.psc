;BEGIN FRAGMENT CODE - Do not edit anything between this and the end comment
;NEXT FRAGMENT INDEX 1
Scriptname HOH110_Vampire Extends TopicInfo Hidden

;BEGIN FRAGMENT Fragment_0
Function Fragment_0(ObjectReference akSpeakerRef)
Actor akSpeaker = akSpeakerRef as Actor
;BEGIN CODE
akSpeaker.SetPlayerTeammate(false)
Alias_Tyranus.GetActorRef().SetRelationshipRank(Game.GetPlayer(), -3)
akspeaker.AddtoFaction(pPlayerEnemyFaction)
akspeaker.SendAssaultAlarm()
akspeaker.StartCombat(Game.GetPlayer())
;END CODE
EndFunction
;END FRAGMENT

;END FRAGMENT CODE - Do not edit anything between this and the begin comment

ReferenceAlias Property Alias_Tyranus Auto
Faction property pplayerenemyfaction auto
