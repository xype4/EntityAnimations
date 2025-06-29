;BEGIN FRAGMENT CODE - Do not edit anything between this and the end comment
;NEXT FRAGMENT INDEX 1
Scriptname DA110_KeshFight Extends TopicInfo Hidden

;BEGIN FRAGMENT Fragment_0
Function Fragment_0(ObjectReference akSpeakerRef)
Actor akSpeaker = akSpeakerRef as Actor
;BEGIN CODE
akspeaker.SetRelationshipRank(Alias_Kesh.GetActorRef(), -3)
akspeaker.StartCombat(Alias_Kesh.GetActorRef())
Alias_Kesh.GetActorRef().StartCombat(Alias_Tyranus.GetActorRef())
;END CODE
EndFunction
;END FRAGMENT

;END FRAGMENT CODE - Do not edit anything between this and the begin comment

ReferenceAlias Property Alias_Tyranus Auto
ReferenceAlias Property Alias_Kesh Auto
