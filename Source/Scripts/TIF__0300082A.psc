;BEGIN FRAGMENT CODE - Do not edit anything between this and the end comment
;NEXT FRAGMENT INDEX 1
Scriptname TIF__0300082A Extends TopicInfo Hidden

;BEGIN FRAGMENT Fragment_0
Function Fragment_0(ObjectReference akSpeakerRef)
Actor akSpeaker = akSpeakerRef as Actor
;BEGIN CODE
StendarrsBeaconLocation.SetCleared()
IF LCO_Vigil_isSelectable.GetValue() == 1
	LocationChangeOwnershipEvent.sendStoryEvent(StendarrsBeaconLocation, none, none, LCO.VigilOfStendarr())
ENDIF
IF LCO_Vigil_isSelectable.GetValue() == 0
	LocationChangeOwnershipEvent.sendStoryEvent(StendarrsBeaconLocation, none, none, LCO.Dawnguard())
ENDIF
;END CODE
EndFunction
;END FRAGMENT

;END FRAGMENT CODE - Do not edit anything between this and the begin comment

Keyword Property LocationChangeOwnershipEvent auto
Location Property StendarrsBeaconLocation auto
GlobalVariable Property LCO_Vigil_isSelectable auto
