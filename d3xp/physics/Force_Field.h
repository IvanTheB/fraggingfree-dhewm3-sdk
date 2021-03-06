/*
===========================================================================

Doom 3 GPL Source Code
Copyright (C) 1999-2011 id Software LLC, a ZeniMax Media company.

This file is part of the Doom 3 GPL Source Code ("Doom 3 Source Code").

Doom 3 Source Code is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Doom 3 Source Code is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Doom 3 Source Code.  If not, see <http://www.gnu.org/licenses/>.

In addition, the Doom 3 Source Code is also subject to certain additional terms. You should have received a copy of these additional terms immediately following the terms and conditions of the GNU General Public License which accompanied the Doom 3 Source Code.  If not, please request a copy in writing from id Software at the address below.

If you have questions concerning this license or the applicable additional terms, you may contact in writing id Software LLC, c/o ZeniMax Media Inc., Suite 120, Rockville, Maryland 20850 USA.

===========================================================================
*/

#ifndef __FORCE_FIELD_H__
#define __FORCE_FIELD_H__

#include "physics/Force.h"
#include "physics/Clip.h"
#include "Entity.h"
#include "AFEntity.h"

/*
===============================================================================

	Force field

===============================================================================
*/

enum forceFieldType {
	FORCEFIELD_UNIFORM,
	FORCEFIELD_EXPLOSION,
	FORCEFIELD_IMPLOSION
};

enum forceFieldApplyType {
	FORCEFIELD_APPLY_FORCE,
	FORCEFIELD_APPLY_VELOCITY,
	FORCEFIELD_APPLY_IMPULSE
};

//ivan start
enum forceFieldMagnitudeType {
	FORCEFIELD_MAGNITUDE_FIXED, //no changes to the specified magnitude
	FORCEFIELD_MAGNITUDE_DISTANCE, //the closer it is, the higher the magnitude is
	FORCEFIELD_MAGNITUDE_DISTANCE_INV
};
//ivan end

class idForce_Field : public idForce {

public:
	CLASS_PROTOTYPE( idForce_Field );

	void				Save( idSaveGame *savefile ) const;
	void				Restore( idRestoreGame *savefile );

						idForce_Field( void );
	virtual				~idForce_Field( void );
						// uniform constant force
	void				Uniform( const idVec3 &force );
						// explosion from clip model origin
	void				Explosion( float force );
						// implosion towards clip model origin
	void				Implosion( float force );
						// add random torque
	void				RandomTorque( float force );
						// should the force field apply a force, velocity or impulse
	void				SetApplyType( const forceFieldApplyType type ) { applyType = type; }
						// make the force field only push players
	void				SetPlayerOnly( bool set ) { playerOnly = set; }
						// make the force field only push monsters
	void				SetMonsterOnly( bool set ) { monsterOnly = set; }
						// clip model describing the extents of the force field
	void				SetClipModel( idClipModel *clipModel );
	
	//ivan start
	void				SetPosition( const idVec3 &newOrigin, const idMat3 &newAxis );
	void				SetWindMode( bool on ){ windMode = on; };
	void				SetMode2D( bool on ) { mode2D = on; }

	// should the force field apply a force, velocity or impulse
	void				SetMagnitudeType( const forceFieldMagnitudeType type ) { magnitudeType = type; }
	void				SetOldVelocityPct( float oldPct ) { oldVelocityPct = oldPct; }
	void				SetOldVelocityProjPct( float oldPct ) { oldVelocityProjPct = oldPct; }
	void				SetVelocityCompensationPct( float compPct ) { velocityCompensationPct = compPct; }
	//void				SetProjectilesMagnitudePct( float projPct ) { projectilesMagnitudePct = projPct; }
	void				SetParentLinearVelocity( const idVec3 &velocity ) { parentLinearVelocity = velocity; }
	void				SetMagnitudeSphere( float radius_min, float radius_max );
	void				SetMagnitudeCylinder( float radius_min, float radius_max );
	void				Swing( float magnitude, float period );
	void				AddToWhiteList( idEntity *ent );
	void				RemoveFromWhiteList( idEntity *ent );
	bool				IsWhiteListed( idEntity *ent );
	void				ClearWhiteList( void );
	void				UseWhitelist( bool on ){ useWhitelist = on; };
	void				ExclusiveMode( bool on ){ exclusiveMode = on; };
	void				IgnoreInactiveRagdolls( bool on ){ ignoreInactiveRagdolls = on; };
	//ivan end


public: // common force interface
	virtual void		Evaluate( int time );

private:
	// force properties
	forceFieldType		type;
	forceFieldApplyType	applyType;
	//ivan start
	forceFieldMagnitudeType		magnitudeType; 
	float				magnitude_sphere_max;
	float				magnitude_sphere_min;
	float				magnitude_cylinder_max;
	float				magnitude_cylinder_min;
	float				oldVelocityPct;
	float				oldVelocityProjPct;
	float				swingMagnitude;
	float				swingPeriod;
	float				velocityCompensationPct;
	bool				useWhitelist;
	bool				exclusiveMode;
	bool				ignoreInactiveRagdolls;
	bool				windMode;
	idList< idEntityPtr<idEntity> >	whiteList;
	idVec3				parentLinearVelocity; //this is only used for calculations, it's not actually applied.
	//ivan end
	float				magnitude;
	idVec3				dir;
	float				randomTorque;
	bool				playerOnly;
	bool				monsterOnly;
	bool				mode2D;
	idClipModel *		clipModel;
	
	//ivan start
	float				GetDistancePct( float distance, float radius_inner, float radius_falloff );
	//ivan end
	
};

#endif /* !__FORCE_FIELD_H__ */
