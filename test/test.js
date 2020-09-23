let input = "";

const behaviour = {
	Unknown: "unknown",
	Dead: "dead",
	Taking: "take",
	Sleeping: "sleep",
	Thinking: "think",
	Eating: "eat"
};

console.log("Starting stdin scan\n---------------------");
process.stdin.on('readable', () => {
	let chunk;
	while (null !== (chunk = process.stdin.read())) {
		input += chunk
		process.stdout.write(chunk);
	}
});

process.stdin.on("end", () => {
	console.log("---------------------\nFinished stdin scan\nNow starting analysis");
	startScans(input);
});

const Color = {
	red(s) {
		return `\x1b[31m${s}\x1b[0m`
	},
	green(s) {
		return `\x1b[32m${s}\x1b[0m`
	},
}

function formatData(data) {
	return data.split("\n").map(v => {
		const output = {
			type: null,
			phil: null,
			line: null,
			time: null
		}

		if (v.endsWith("has died"))
			output.type = behaviour.Dead;
		else if (v.endsWith("has taken a fork"))
			output.type = behaviour.Taking;
		else if (v.endsWith("is sleeping"))
			output.type = behaviour.Sleeping;
		else if (v.endsWith("is eating"))
			output.type = behaviour.Eating;
		else if (v.endsWith("is thinking"))
			output.type = behaviour.Thinking;
		else
			output.type = behaviour.Unknown;

		output.phil = parseInt(v.split(" ")[1]);
		output.time = BigInt(v.split(" ")[0]);
		output.line = v;
		return output;
	})
	.filter(v => v.line.length > 1);
}

function countBehaviour(actions, type, id = -1) {
	return actions.reduce((p, v) => {
		if (v.type == type) {
			if (id == -1 || v.phil == id)
				return p + 1;
		}
		return p;
	}, 0);
}

function findLatestBehaviour(actions, type, id = -1) {
	return [...actions].reverse().find((v) => {
		if (v.type == type) {
			if (id == -1 || v.phil == id)
				return true;
		}
		return false;
	});
}

function getCurrentForks(actions, id) {
	let counter = 0;
	[...actions].reverse().find((v) => {
		if (v.phil != id)
			return false;
		if (v.type == behaviour.Eating) {
			return true;
		}
		if (v.type == behaviour.Taking) {
			counter++;
		}
		return false;
	});
	return counter;
}

function startScans(data) {
	const actions = formatData(data);

	const unknownCount = countBehaviour(actions, behaviour.Unknown);
	const diedCount = countBehaviour(actions, behaviour.Dead);

	if (diedCount == 0) {
		let state = {};

		actions.forEach(v => {
			if (v.type == behaviour.Eating) {
				if (!state["philosopher " + v.phil])
					state["philosopher " + v.phil] = 0;
				state["philosopher " + v.phil]++;
			}
		});

		console.log("No dead found, eat counts:\n" + Object.keys(state).map(v => `${v}: ${state[v]}`).join("\n"));
		return
	}

	const latestDied = findLatestBehaviour(actions, behaviour.Dead);
	let latestEat = findLatestBehaviour(actions, behaviour.Eating, latestDied.phil);
	latestEat = latestEat ? latestEat : actions[0];
	const forksInPossesion = getCurrentForks(actions, latestDied.phil);

	console.log(
		`----------------\n` +
		`Unknown behaviour: ${unknownCount > 0 ? Color.red(unknownCount) : Color.green(unknownCount)}\n` + 
		`Death count: ${diedCount != 1 ? Color.red(diedCount) : Color.green(diedCount)}\n` + 
		`Philosopher who died: ${latestDied.phil}\n` +
		`Time till last eat: ${latestDied.time - latestEat.time}ms\n` +
		`Forks in possesion: ${forksInPossesion > 1 ? Color.red(forksInPossesion) : Color.green(forksInPossesion)}`
	)
}
