open TestFramework;
open TestReconciler;
open Assert;

let root = Implementation.{name: "root", element: View};
let div = Implementation.{name: "Div", element: View};
let text = t => Implementation.{name: "Text", element: Text(t)};
let box = t => Implementation.{name: "Box", element: Text(t)};

let render = render(root);

describe("Test initial render", ({test}) =>
  test("It should correctly insert nodes", ({expect}) => {
    let state = render(<Components.BoxWrapper />) |> executeSideEffects;
    let snapshot = [
      Implementation.BeginChanges,
      MountChild(div, box("ImABox"), 0),
      MountChild(root, div, 0),
      CommitChanges,
    ];

    expect.ext.mounted(state).toMatch(snapshot);
  })
);

describe("Test rendering list children", ({test}) =>
  test("It inserts two boxes in a div", ({expect}) => {
    let state = render(
      Components.(
        <Div> <Box title="ImABox1" /> <Box title="ImABox2" /> </Div>
      )
    ) |> executeSideEffects;
    let snapshot = [
      Implementation.BeginChanges,
      MountChild(div, box("ImABox1"), 0),
      MountChild(div, box("ImABox2"), 1),
      MountChild(root, div, 0),
      CommitChanges,
    ];

    expect.ext.mounted(state).toMatch(snapshot);
  })
);