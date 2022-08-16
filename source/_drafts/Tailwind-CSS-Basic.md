---
title: Tailwind CSS Basic
tags: CSS
categories: Frontend
---





1. 引入tailwind模块:

   ```
   npm install -D tailwindcss
   ```

   or:

   ```
   yarn add tailwindcss -D
   ```

2. 进入项目目录，创建Tailwind CSS配置文件( `tailwind.config.js` ):

   ```
   npx tailwindcss init
   ```

3. Add the Tailwind directives to your CSS

   Add the `@tailwind` directives for each of Tailwind’s layers to your main CSS file.

   ```
   @tailwind base;
   @tailwind components;
   @tailwind utilities;
   ```

4. Start the Tailwind CLI build process

   Run the CLI tool to scan your template files for classes and build your CSS.

   ```
   npx tailwindcss -i ./src/input.css -o ./dist/output.css --watch
   ```

   

5. Start using Tailwind in your HTML

   Add your compiled CSS file to the `<head>` and start using Tailwind’s utility classes to style your content.

   ```
   ```

   
