[Wireframe Triangle](wTriangle.html): Drew a an equilateral triangle, with no fill using `gl.LINE_LOOP`. The triangle is generated using trigonometric math, not hard points. Vertex Shader finds the points and fragment shader gives it the color.

[An almost circle, 10 Sided Polygon](polyCircle.html): Drew an polygon with 10 sides using the `gl.TRIANGLE_FAN`. where triangles are created at various angles from the origin and two other points to give the polygon its shape. Then colored using a fragment shader

[Truly Circle Polygon](turlyCircle.html): Just a polygon like before but with more triangle fans to make it look like a circle.

[5 Pointed Star](star.html): Created a star shape with 5 points. We check what the radius needs to be by using the mod function, inner radius is then set to .5 while outer radius is set to 1. the Radius then influences the position of the point that will be placed by `gl_Position`. We need 10 fans in total if we want 5 pointed star. the number of vertices will be 12 as we need one starting vertex in the origin and one that overlaps the starting vertex to finish the shape. I have added a variable called `starPoints` that dynamically changes the number of points our star can have.

[Spinney Star](spinnyStar.html): Basically the same the previous star but we change the angle of the star points based on the time, we it looks like the star is spinning as time changes.

[FUN STUFF: Explodey Star That Spins](explodeyStarThatSpins.html): I started having fun here. now the color is also influenced by the change is time and the radius also changes. So the star starts small grows to its max size and returns to being small. This is repeated forever. I accomplished this by passing time into the sine function which then changes the radius. Similar stuff was done to color as well. 

[Extra Credit FUN STUFF](extraExplodeyStarThatSpins.html):  For extra credit but still fun. Exported the value of the radius to the fragment shader from the vertex shader to create a color gradient on the explodey star. It was cool.