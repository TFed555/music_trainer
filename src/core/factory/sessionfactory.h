#ifndef SESSIONFACTORY_H
#define SESSIONFACTORY_H
#pragma once

#include "registryfactory.h"
#include "../common/interfaces/IExerciseWidget.h"
#include "../sessions/common/isession.h"
#include "../../audio/playback/noteplayer.h"

using SessionFactory = RegistryFactory<ExerciseType, ISession, NotePlayer*, QObject*>;

#endif // SESSIONFACTORY_H
